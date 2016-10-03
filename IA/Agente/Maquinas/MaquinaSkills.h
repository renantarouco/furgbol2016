#ifndef MAQUINA_SKILLS_H
#define MAQUINA_SKILLS_H

#include <Skill.h>
#include <DadosSensoriais.h>
#include <Percepcao.h>

class Agente;

/**
 * Máquina que contém as skills a serem executadas.
 * Esta máquina é selecionada por uma tática tendo parametros passados.
 * O objetivo da máquina de estados é gerar um comando, e isso é feito a partir de transições que andam ao longo das skills.
 * Quando as condições de uma skill forem satisfeitas ela ira gerar um comando e a máquina vai parar.
 * As máquinas criadas sempre guardam o ultimo estado onde ela parou ( gerou comando).
 * A máquina de skills é uma classe abstrata que será redefinida para cada tipo de máquina existente.
 * Entenda tipo de máquina como máquina que tem um conjunto diferente de skills e transições.
 *
 */
class MaquinaSkills{

public:
        /**
            Parametro da Maquina de Skills que serão usados para identificar as habilidades que poderão ser usadas pelo robô
        */
        enum Parametro {
            CHUTE_BAIXO = 0,
            CHUTE_ALTO = 1,
            SEM_CHUTE = 2,
            TEM_DRIBLE = 3,
            PASSA_POR_TRAS = 4,
            GIRA_EIXO = 5,
            FICAR_PARADO = 6,
            EMPURRA_BOLA = 7,
            NAO_GIRA = 8,
            GIRA_NA_BOLA = 9
        };

        MaquinaSkills();
        virtual ~MaquinaSkills()=0;

        /**
            Função que verifica se o parametro está inserido na Maquina
            @param p Parametro que queremos procurar
            @return True se existir o parametro, False senão existir
        */
        bool parametroExiste(Parametro p);

        /**
            Função que faz uma percepcao do Modelo de Mundo, analisando as informações e setando os novos
            valores nos dados sensorias da maquina para serem analisados posteriormente
        */
        virtual void perceber()=0;

        /**
            Função que analisa os dados sensoriais e identifica qual Skill é a melhor para o momento
            atual da partida, se precisar transitar de uma skill para outra ele fará, caso contrário irá
            continuar a executar a skill do estado anterior
        */
        virtual void transitar()=0;

        /**
            Função que gera o Comando que o robô irá executar.
            @param agente Agente que irá executar o comando
        */
        virtual void executar(Agente* agente)=0;

protected:
        int idRobo;
        Skill* skillAtual; ///< indica qual a skill que está sendo executada
        map<int, Skill*> skills; ///< Vetor com as Skills que poderam ser executadas pela Maquina

        DadosSensoriais dadosSensoriais; ///< Dados que serão usados para identificar qual Skill iremos executar
        vector<Parametro> parametros; ///< Parametros da Maquina usados para sabermos quais habilidades o robô poderá usar
        Percepcao percepcao; ///< Percebe acontecimentos na partida e seta as novas informações nos dados sensoriais
};
#endif
