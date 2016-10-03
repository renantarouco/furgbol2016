#include "Geometria.h"

Geometria::Geometria()
{
}

float Geometria::produtoVetorial2D(Vetor u, Vetor v)     //  * Trucagem ! O produto vetorial nao eh definido
{                                               //  * no espaco bidimensional , porem assumindo o dois vetores coplanares( com z =0)
    return ((u.x()*v.y())-(v.x()*u.y()));   //  * tem-se como retorno a componente x=0, y=0 e uma componente z retornada por essa funcao;
}

float Geometria::calcularAnguloVetores(Vetor u, Vetor v){


    float angle;
    /// Transforma em unitario

    float modulo_u, modulo_v;
    modulo_u = sqrt(u.squared_length());
    modulo_v = sqrt(v.squared_length());

    if(modulo_u < 0.001 || modulo_v < 0.001)
    {
        return 0;
    }
    else
    {
        float dot_product = u.x()*v.x() + u.y()*v.y();

        float aux = dot_product/(modulo_u*modulo_v);

        if(aux > 1.0f) {
            angle = 0;
        }else if(aux < -1.0f){
            angle = M_PI;
        }else{
            angle = acosf(aux);
        }
        return angle;
    }
}



bool Geometria::colisao(Ponto &A, Ponto &B, Circulo circ)
{
    Reta reta(A , B);
    Retangulo retangulo( A , B );

    vector<Objeto> intersecs;
    intersecs.reserve(2);

    intersection(circ , reta , back_inserter(intersecs));
    for (unsigned int j = 0; j < intersecs.size(); j ++)
    {
        if(const pair< ArcPonto, unsigned> *ponto = CGAL::object_cast< pair< ArcPonto, unsigned> > (&(intersecs[j])))
        {
            Ponto p(ponto->first.x() , ponto->first.y() );
            if(!retangulo.has_on_unbounded_side( p ) )
                return true;
        }
    }
    intersecs.clear();

    return false;
}

Ponto Geometria::calcularPontoEmRetaComDesloc(const Ponto &pontoNaReta, const Reta &reta, float distAfastamento){

    /// Verificando se a reta é vertical para acrescentar o deslocamento em y
    if(reta.is_vertical()){
        return Ponto(pontoNaReta.x(), pontoNaReta.y() + distAfastamento); /// Se for vertical basta somarmos o deslocamento em y

        /// Verificando se a reta é horizontal para acrescentar o deslocamento em x
    }else if(reta.is_horizontal()){
        return Ponto(pontoNaReta.x() + distAfastamento, pontoNaReta.y()); /// Se for horizontal basta somarmos o deslocamento em x
    }

    /// Senão for nenhuma dos casos anteriores a reta é inclinada.
    /// @todo verificar se esse atan está correto
    float deslocX = cos(atan(reta.a()/reta.b())) * distAfastamento; /// Calculando o deslocamento que terá no eixo das abscissas

    /// Calculando as novas coordenadas do Ponto
    float x = pontoNaReta.x() + deslocX; /// Calculando o valor de x com base no deslocamento e no valor anterior
    float y = reta.y_at_x(pontoNaReta.x() + deslocX); /// Calculando o valor de y com base no deslocamento e no valor anterior

    /// Somando a distância em x apartir do ponto, e pegando o y do ponto na reta.
    return Ponto(x, y);
}

bool Geometria::interseccaoRetaSemiCirculo(const Arco& semiCirculo, const Reta& reta, Ponto& interseccao){
    vector<Objeto> objetosInterseccao; ///< Vetor com os pontos que faze interseccao da reta com o semiCirculo
    objetosInterseccao.reserve(2);

    /// Pegando os pontos de interseccao da reta com o semicirculo
    intersection(semiCirculo, reta, back_inserter(objetosInterseccao));
    /// Verificando quantas raízes existem na interseccao
    if(objetosInterseccao.size() > 1){
        //pair< ArcPonto, unsigned> *ponto = CGAL::object_cast< pair< ArcPonto, unsigned> > (&(objetosInterseccao[0]));
        // cout << " Warning! mais de um ponto interceptando o semi circulo " << endl;
        /// AVISO Essa funcao deve ser melhor tratada , pois pode existir mais de um ponto interseptando.
        /// Senão tivermos interseccao retornaremos false
        cout<<objetosInterseccao.size()<<endl;
        return false;
        //cout<<"INTER====================================>"<<'('<<ponto->first.x()<<','<<ponto->first.y()<<')' <<endl;
    }else if(objetosInterseccao.size() == 0){
        return false;

        /// Se nenhuma das condições acima for satisfeita, então iremos pegar o ponto de interseccao e retornar ele
    }else{

        /// Verificando se o ponto não está com erro.
        if(const pair< ArcPonto, unsigned> *ponto = CGAL::object_cast< pair< ArcPonto, unsigned> > (&(objetosInterseccao[0]))){
            cout << "UM PONTO" << endl;
            interseccao = Ponto(ponto->first.x() , ponto->first.y());
        }else{
            cout << "ERRO NO PONTO" << endl;
            return false;
        }
    }
    return true;
}

bool Geometria::isInterseccaoSegmentoReta(const Segmento& segmento, const Reta& reta){
    return do_intersect(segmento, reta);
}

bool Geometria::isInterseccaoSegmentoReta(const Segmento& segmento, const Reta& reta, Ponto& interseccao){
    /// Pegando o objeto que faz interseccao entre a reta e o segmento
    Objeto objetoInterseccionado = intersection(segmento, reta);

    /// Verificando se o Objeto é válido e setando dentro da variável
    return assign(interseccao, objetoInterseccionado);
}

vector<Ponto> Geometria::interseccaoCirculoCirculo(const Circulo& circulo1, const Circulo& circulo2){

    /// Vetor com os pontos que fazem interseccao entre os circulos
    vector<Objeto> objetosInterseccao;

    /// Fazendo a interseccao entre os circulos e setando os pontos
    intersection(circulo1, circulo2, back_inserter(objetosInterseccao));

    vector<Ponto> pontosInterseccao; /// Vetor com os pontos que fazem interseccao entre os circulos

    if(objetosInterseccao.size() < 2){
        pontosInterseccao =  vector<Ponto>(2, Ponto(0.0, 0.0)); /// Vetor com os pontos que fazem interseccao entre os circulos
        cout << " Warning ! menos de 2 pontos interceptando os circulos." << endl;
    }else{
        foreach(Objeto objeto, objetosInterseccao){

            /// Transformando o objeto em um ponto
            if(const pair< ArcPonto, unsigned> *ponto = CGAL::object_cast< pair< ArcPonto, unsigned> > (&objeto))
                pontosInterseccao.push_back(Ponto(ponto->first.x() , ponto->first.y()));
        }
    }

    return pontosInterseccao;
}
