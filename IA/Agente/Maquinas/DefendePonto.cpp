#include "DefendePonto.h"
#include <Sistema.h>

DefendePonto::DefendePonto(){
    /// Setando as skills que podem ser usadas nessa Maquina e tambem setando no construtor as velocidades de aproximacao, deslocamente e angular de cada uma
    skills[Skill::VAI_PARA_ALVO] = new VaiParaAlvo();
    skills[Skill::VIRA_PARA_BOLA] = new ViraParaBola();
    skills[Skill::GIRA_EIXO] = new GiraEixo();
    skills[Skill::MANTEM_POSICAO] = new MantemPosicao();

    /// setando o estado inicial
    skillAtual = skills[Skill::VAI_PARA_ALVO];
}

DefendePonto::~DefendePonto(){
    map<int, Skill*>::iterator it;
    for(it = skills.begin(); it != skills.end(); it++){
        delete it->second;
    }
    skills.clear();
}

void DefendePonto::perceber(){
    /// verificando se o robo está de frente para a bola
    dadosSensoriais.deFrenteParaBola = percepcao.isFrenteParaBola();

    /// verificando se o robo está no alvo em que deveria estar
    dadosSensoriais.noAlvoMarcado = percepcao.isAlvoMarcado(Sistema::modeloMundo.getRoboEq(idRobo)->getAlvoFinal());

    /// caso a bola não esteja dentro do campo, ou caso o robo tenha que realmente ficar parado iremos fazer ele ficar na ultimo posicao
    dadosSensoriais.manterPosicao = !percepcao.isBolaDentroCampo() || ficarParado;

    /// verificando se teremos que fazer o robo ficar gerando no proprio eixo
    //    dadosSensoriais.girarEixo = parametroExiste(MaquinaSkills::GIRA_EIXO);
}

void DefendePonto::transitar(){

    /// Verificando qual é a skill atual
    switch (skillAtual->getTipo()){

    case Skill::VAI_PARA_ALVO:

        /// Caso o robo tenha que manter a posicação ou caso ele já esteja no alvo marcado iremos executar a SKILL de MANTER_POSICAO
        if(dadosSensoriais.manterPosicao || dadosSensoriais.noAlvoMarcado){
            skillAtual = skills[Skill::MANTEM_POSICAO];
        }

        break;

    case Skill::MANTEM_POSICAO:

        /// caso o robo não tenha que ficar realmente parado iremos analisar
        if(!dadosSensoriais.manterPosicao){

            /// caso o robo não esteja já no alvo marcado iremos mandar ele ir
            if(!dadosSensoriais.noAlvoMarcado){
                skillAtual = skills[Skill::VAI_PARA_ALVO];
            }else if(!dadosSensoriais.deFrenteParaBola){
                skillAtual = skills[Skill::VIRA_PARA_BOLA];
            }

            /// caso o robo não esteja de frente para a bola iremos mandar ele ficar de frente
        }else if(dadosSensoriais.noAlvoMarcado && dadosSensoriais.noAlvoMarcado){
            skillAtual = skills[Skill::VIRA_PARA_BOLA];
        }

        break;

    case Skill::VIRA_PARA_BOLA:

        /// caso o robo não esteja no alvo marcado iremos fazer ele ir até o alvo
        if(!dadosSensoriais.noAlvoMarcado){
            skillAtual = skills[Skill::VAI_PARA_ALVO];

            /// caso o robo esteja de frente para bola iremos manter a posicao
        }else if(dadosSensoriais.deFrenteParaBola){
            skillAtual = skills[Skill::MANTEM_POSICAO];
        }

        break;

    default:
        break;
    }
}

void DefendePonto::setDados(const Ponto &_alvo, const vector<MaquinaSkills::Parametro> &_parametros)
{
    alvo = _alvo;
    parametros = _parametros;

    /// indica que o robo terá que ficar parado
    ficarParado = parametroExiste(MaquinaSkills::FICAR_PARADO);
}

void DefendePonto::executar(Agente* agente){
    idRobo = agente->getId(); /// Setando o id robô que irá executar a máquina de skills
    percepcao.setIdRobo(idRobo); /// Iniciando o objeto que irá fazer a percepcao do mundo para a skill

    /// Verificando se o alvo do robo foi alterado e setando o novo alvo
    Sistema::modeloMundo.getRoboEq(idRobo)->setAlvoMudou(percepcao.isAlvoMudou(alvo));
    Sistema::modeloMundo.getRoboEq(idRobo)->setAlvoFinal(alvo);

    /// iremos atualizar os dados sensoriais da maquina para saber se iremos transitar ou não para outro estado
    perceber();

    /// Executando a transição de estado, caso os dados sensoriais sejam os mesmos então iremos continuar executando a mesma skill
    transitar();

    /// Executando a skill
    skillAtual->executar(agente); /// Gerando o comando da skill para o robô selecionado.
}
