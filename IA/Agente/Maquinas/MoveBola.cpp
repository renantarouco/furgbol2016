#include "MoveBola.h"
#include "Sistema.h"

MoveBola::MoveBola(){
    chuteBaixo = chuteAlto = false;

    skills[Skill::VAI_PARA_ALVO] = new VaiParaAlvo();
    skills[Skill::GIRA_HORARIO] = new GiraHorario();
    skills[Skill::GIRA_ANTI_HORARIO] = new GiraAntiHorario();
    skills[Skill::CHUTA] = new Chuta();
    skills[Skill::VIRA_PARA_BOLA] = new ViraParaBola();
    skills[Skill::VAI_PARA_BOLA] = new VaiParaBola();
    skills[Skill::EMPURRA_BOLA] = new EmpurraBola();
    skills[Skill::MANTEM_POSICAO] = new MantemPosicao();
    skills[Skill::CHUTA_ALTO] = new ChutaAlto();
    skills[Skill::GIRA_HORARIO_DRIBLE] =  new GiraHorarioDrible();
    skills[Skill::DOMINA_BOLA] =  new DominaBola();

    /// setando a skill inicial
    skillAtual = skills[Skill::VAI_PARA_ALVO];
}

MoveBola::~MoveBola()
{
    map<int, Skill*>::iterator it;
    for(it = skills.begin(); it != skills.end(); it++){
        delete it->second;
    }
    skills.clear();
}

void MoveBola::perceber(){
    dadosSensoriais.dentroRaioAprox = percepcao.isDentroRaioAprox();
    dadosSensoriais.deFrenteParaBola =  percepcao.isFrenteParaBola();
    dadosSensoriais.comAnguloDeChute = percepcao.isAnguloParaChute(anguloChute);
    dadosSensoriais.noAlvoMarcado = percepcao.isAlvoMarcado(alvoAprox);
    dadosSensoriais.girarHorario = percepcao.getSentidoMaisPerto(alvoAprox);
    dadosSensoriais.manterPosicao = !percepcao.isBolaDentroCampo();
    dadosSensoriais.carregarBola = percepcao.isCarregarBola();
    dadosSensoriais.bolaPertoParaChute = percepcao.isBolaPertoParaChute();
    dadosSensoriais.deFrenteParaBolaDrible =  percepcao.isFrenteParaBolaDrible();
    dadosSensoriais.bolaMoveu = percepcao.isBolaChutada();
    dadosSensoriais.bolaSaindoPelaLateral = percepcao.isBolaQuaseSaindoCampo();
}

void MoveBola::transitar(){


    cout<<"===========================================>"<<skillAtual->getTipo()<<endl;
    switch (skillAtual->getTipo())
    {
    case Skill::VAI_PARA_ALVO:

        /// se tivermos que manter a posicao iremos executar a skill mantem posicao
        if(dadosSensoriais.manterPosicao) {
            skillAtual = skills[Skill::MANTEM_POSICAO];

            /// verificar se o robo está dentro do raio de aproximação e se ele tem que girar no sentido horario para ficar de frente pro gol adv
        }else if(dadosSensoriais.noAlvoMarcado){

            /// verificando se a bola está perto para chutar
            if(dadosSensoriais.bolaPertoParaChute){

                /// verificando se é viável chutar e se o robô tem chute
                if(chuteBaixo){
                    skillAtual = skills[Skill::CHUTA];
                }else if(chuteAlto){
                    skillAtual = skills[Skill::CHUTA_ALTO];
                }else{
                    skillAtual = skills[Skill::EMPURRA_BOLA];
                }

                /// fazendo o dominio da bola para poder chutar
            }else{
                skillAtual = skills[Skill::DOMINA_BOLA];
            }
            //            /// verificando se iremos girar horario ou antihorario para ficar de frente para o gol adv
            //            if(dadosSensoriais.girarHorario){
            //                skillAtual = skills[Skill::GIRA_HORARIO];
            //            }else{
            //                skillAtual = skills[Skill::GIRA_ANTI_HORARIO];
            //            }
        }

        break;

    case Skill::MANTEM_POSICAO:

        /// caso o robo não precisa ficar na posicao iremos mandar ele ir para o alvo calculado
        if(!dadosSensoriais.manterPosicao){
            skillAtual = skills[Skill::VAI_PARA_ALVO];
        }
        break;

        //    case Skill::GIRA_ANTI_HORARIO:
        //    case Skill::GIRA_HORARIO:

        //        /// verificando se o robô está em direção do gol adversario
        //        if(dadosSensoriais.comAnguloDeChute){

        //            /// verificando se é viável chutar e se o robô tem chute
        //            if(chuteBaixo){
        //                skillAtual = skills[Skill::CHUTA];
        //            }else if(chuteAlto){
        //                skillAtual = skills[Skill::CHUTA_ALTO];
        //            }else{
        //                skillAtual = skills[Skill::EMPURRA_BOLA];
        //            }

        //            /// se o robo não estiver mais dentro do raio de aproximaçao iremos mandar ele ir até ficar dentro do alvo
        //        }else if(!dadosSensoriais.dentroRaioAprox){
        //            skillAtual = skills[Skill::VAI_PARA_ALVO];
        //        }
        //        break;

    case Skill::DOMINA_BOLA:

        /// se não estiver no alvo mandar ir para o alvo
        if(!dadosSensoriais.comAnguloDeChute){
            skillAtual = skills[Skill::VAI_PARA_ALVO];
            cout<<"com angulo"<<endl;
            /// caso esteja no alvo e a bola está perto, mandaremos chutar
        }else if(dadosSensoriais.bolaPertoParaChute){

            /// verificando se é viável chutar e se o robô tem chute
            if(chuteBaixo){
                skillAtual = skills[Skill::CHUTA];
                cout<<"chuta"<<endl;
            }else if(chuteAlto){
                skillAtual = skills[Skill::CHUTA_ALTO];
                cout<<"chuta alto"<<endl;
            }else{
                skillAtual = skills[Skill::EMPURRA_BOLA];
                cout<<"empurra"<<endl;
            }
        }

        break;

    case Skill::CHUTA:
    case Skill::CHUTA_ALTO:
    case Skill::EMPURRA_BOLA:

        /// se não está no alvo, iremos mandar ir para o alvo
        if(!dadosSensoriais.noAlvoMarcado){
            skillAtual = skills[Skill::VAI_PARA_ALVO];

            /// se não estiver perto da bola, iremos mandar dominar para poder chutar
        }else if(!dadosSensoriais.bolaPertoParaChute){
            skillAtual = skills[Skill::DOMINA_BOLA];
        }

        break;
    }
}

void MoveBola::setDados(const Ponto& _alvoAprox, const Ponto& _alvoChute, vector<Parametro> _parametros){
    alvoAprox = _alvoAprox;
    alvoChute = _alvoChute;
    parametros = _parametros;

    /// verificando se o robo tem chute
    chuteBaixo = parametroExiste(MaquinaSkills::CHUTE_BAIXO);
    chuteAlto = parametroExiste(MaquinaSkills::CHUTE_ALTO);
}

void MoveBola::setDados(const Ponto& _alvoAprox, const Ponto& _alvoChute, float _anguloChute, const vector<Parametro>& _parametros){
    alvoAprox = _alvoAprox;
    alvoChute = _alvoChute;
    anguloChute = _anguloChute;
    parametros = _parametros;

    /// verificando se o robo tem chute
    chuteBaixo = parametroExiste(MaquinaSkills::CHUTE_BAIXO);
    chuteAlto = parametroExiste(MaquinaSkills::CHUTE_ALTO);
}

void MoveBola::executar(Agente* agente)
{
    idRobo = agente->getId();
    percepcao.setIdRobo(idRobo);

    /// O alvo de aproximacao tem que ter sido setado.
    Sistema::modeloMundo.getRoboEq(idRobo)->setAlvo(alvoAprox);
    Sistema::modeloMundo.getRoboEq(idRobo)->setAlvoFinal(alvoAprox);
    Sistema::modeloMundo.getRoboEq(idRobo)->setAlvoChute(alvoChute);
    Sistema::modeloMundo.getRoboEq(idRobo)->setAlvoMudou(percepcao.isAlvoMudou(alvoAprox));

    /// iremos atualizar os dados sensoriais da maquina para saber se iremos transitar ou não para outro estado
    perceber();

    /// Executando a transição de estado, caso os dados sensoriais sejam os mesmos então iremos continuar executando a mesma skill
    transitar();

    /// Executando a skill
    skillAtual->executar(agente); /// Gerando o comando da skill para o robô selecionado.
}
