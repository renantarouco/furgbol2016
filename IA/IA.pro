#-------------------------------------------------
#
# Project created by QtCreator 2013-08-06T19:44:29
#
#-------------------------------------------------

QT += core gui network
QT += network

TARGET = IA
TEMPLATE = app

INCLUDEPATH +=  ../ProtoLIB
INCLUDEPATH += /home/nautec/Downloads
LIBS += -L../ProtoLIB -lproto

INCLUDEPATH += Utils \
    Sistema \
    Sistema/Configuração \
    Sistema/Barramentos \
    Agente \
    Agente/Taticas \
    Avaliador \
    Comunicacao \
    GDC \
    Agente/Maquinas \
    Agente/Skills \
    Agente/Navegador \
    ModeloMundo \
    Geometria

HEADERS += \
    Agente/Comando.h \
    Agente/Montador.h \
    Agente/Agente.h \
    Agente/Maquinas/Percepcao.h \
    Agente/Maquinas/MoveBola.h \
    Agente/Maquinas/MaquinaSkills.h \
    Agente/Maquinas/DefendePonto.h \
    Agente/Maquinas/DadosSensoriais.h \
   # Agente/Navegador/Obstaculo.h \
    Agente/Navegador/Navegador.h \
    Agente/Navegador/KDTree.h \
    Agente/Navegador/KDNodo.h \
    Agente/Skills/ViraParaBola.h \
    Agente/Skills/ViraParaAlvo.h \
    Agente/Skills/VaiParaBola.h \
    Agente/Skills/VaiParaAlvoDevagar.h \
    Agente/Skills/VaiParaAlvo.h \
    Agente/Skills/Skill.h \
    Agente/Skills/MantemPosicao.h \
    Agente/Skills/GiraHorarioDrible.h \
    Agente/Skills/GiraHorario.h \
    Agente/Skills/GiraEixo.h \
    Agente/Skills/GiraAntiHorario.h \
    Agente/Skills/EmpurraBola.h \
    Agente/Skills/DominaBola.h \
    Agente/Skills/ChutaAlto.h \
    Agente/Skills/Chuta.h \
    Agente/Skills/CarregaBola.h \
    Agente/Taticas/Tatica.h \
    Agente/Taticas/RoubaBola.h \
    Agente/Taticas/ReceberPasse.h \
    Agente/Taticas/RecebePasseCurto.h \
    Agente/Taticas/PosicionaSegmento.h \
    Agente/Taticas/PosicionaPerdaBola.h \
    Agente/Taticas/PosicionaChute.h \
    Agente/Taticas/Posiciona.h \
    Agente/Taticas/PasseLongo.h \
    Agente/Taticas/PasseCurto.h \
    Agente/Taticas/MarcarSaidaBola.h \
    Agente/Taticas/Marcar.h \
    Agente/Taticas/Limpa.h \
    Agente/Taticas/Halt.h \
    Agente/Taticas/Gira.h \
    Agente/Taticas/DefendePenalty.h \
    Agente/Taticas/DefendeGol.h \
    Agente/Taticas/Chute.h \
    Agente/Taticas/AndarReto.h \
    Avaliador/AvaliadorRobo.h \
    Avaliador/Avaliador.h \
    Comunicacao/Serial.h \
    Comunicacao/ProtocoloSerial.h \
    Comunicacao/Comunicador.h \
    Comunicacao/CommunicationBUS.h \
#    Comunicacao/IAMonitorador.h \
    GDC/Seletor.h \
    GDC/Jogada.h \
    GDC/GerenteDeliberativoCentral.h \
    GDC/Executor.h \
    GDC/Carregador.h \
    Geometria/Poligono.h \
    #Geometria/ObstaculoBola.h \
    Geometria/Geometria.h \
    Geometria/Circulo.h \
    Geometria/Campo.h \
    Geometria/Area.h \
    ModeloMundo/Robo.h \
    ModeloMundo/ModeloMundo.h \
    ModeloMundo/Bola.h \
    Sistema/Sistema.h \
    Sistema/Configuração/ConfigTeste.h \
    Sistema/Configuração/ConfigMontador.h \
    Sistema/Configuração/ConfigComunicacao.h \
    Sistema/Configuração/ConfigAvaliador.h \
    Sistema/Configuração/Config.h \
    Utils/Relogio.h \
    Utils/Definitions.h \
    Agente/Taticas/DefesaCirculo.h \
    Agente/Taticas/DefesaArea.h \
    Agente/Taticas/MarcarAreaAdv.h

SOURCES += main.cpp \
    Agente/Comando.cpp \
    Agente/Montador.cpp \
    Agente/Agente.cpp \
    Agente/Maquinas/Percepcao.cpp \
    Agente/Maquinas/MoveBola.cpp \
    Agente/Maquinas/MaquinaSkills.cpp \
    Agente/Maquinas/DefendePonto.cpp \
    Agente/Maquinas/DadosSensoriais.cpp \
    #Agente/Navegador/Obstaculo.cpp \
    Agente/Navegador/Navegador.cpp \
    Agente/Navegador/KDTree.cpp \
    Agente/Navegador/KDNodo.cpp \
    Agente/Skills/ViraParaBola.cpp \
    Agente/Skills/ViraParaAlvo.cpp \
    Agente/Skills/VaiParaBola.cpp \
    Agente/Skills/VaiParaAlvoDevagar.cpp \
    Agente/Skills/VaiParaAlvo.cpp \
    Agente/Skills/Skill.cpp \
    Agente/Skills/MantemPosicao.cpp \
    Agente/Skills/GiraHorarioDrible.cpp \
    Agente/Skills/GiraHorario.cpp \
    Agente/Skills/GiraEixo.cpp \
    Agente/Skills/GiraAntiHorario.cpp \
    Agente/Skills/EmpurraBola.cpp \
    Agente/Skills/DominaBola.cpp \
    Agente/Skills/ChutaAlto.cpp \
    Agente/Skills/Chuta.cpp \
    Agente/Skills/CarregaBola.cpp \
    Agente/Taticas/Tatica.cpp \
    Agente/Taticas/RoubaBola.cpp \
    Agente/Taticas/ReceberPasse.cpp \
    Agente/Taticas/RecebePasseCurto.cpp \
    Agente/Taticas/PosicionaSegmento.cpp \
    Agente/Taticas/PosicionaPerdaBola.cpp \
    Agente/Taticas/PosicionaChute.cpp \
    Agente/Taticas/Posiciona.cpp \
    Agente/Taticas/PasseLongo.cpp \
    Agente/Taticas/PasseCurto.cpp \
    Agente/Taticas/MarcarSaidaBola.cpp \
    Agente/Taticas/Marcar.cpp \
    Agente/Taticas/Limpa.cpp \
    Agente/Taticas/Halt.cpp \
    Agente/Taticas/Gira.cpp \
    Agente/Taticas/DefendePenalty.cpp \
    Agente/Taticas/DefendeGol.cpp \
    Agente/Taticas/Chute.cpp \
    Agente/Taticas/AndarReto.cpp \
    Avaliador/AvaliadorRobo.cpp \
    Avaliador/Avaliador.cpp \
    Comunicacao/Serial.cpp \
    Comunicacao/ProtocoloSerial.cpp \
    Comunicacao/Comunicador.cpp \
    Comunicacao/CommunicationBUS.cpp \
#    Comunicacao/IAMonitorador.cpp \
    GDC/Seletor.cpp \
    GDC/Jogada.cpp \
    GDC/GerenteDeliberativoCentral.cpp \
    GDC/Executor.cpp \
    GDC/Carregador.cpp \
    Geometria/Poligono.cpp \
    #Geometria/ObstaculoBola.cpp \
    Geometria/Geometria.cpp \
    Geometria/Circulo.cpp \
    Geometria/Campo.cpp \
    Geometria/Area.cpp \
    ModeloMundo/Robo.cpp \
    ModeloMundo/ModeloMundo.cpp \
    ModeloMundo/Bola.cpp \
    Sistema/Sistema.cpp \
    Sistema/Configuração/ConfigTeste.cpp \
    Sistema/Configuração/ConfigMontador.cpp \
    Sistema/Configuração/ConfigComunicacao.cpp \
    Sistema/Configuração/ConfigAvaliador.cpp \
    Sistema/Configuração/Config.cpp \
    Utils/Relogio.cpp \
    Agente/Taticas/DefesaCirculo.cpp \
    Agente/Taticas/DefesaArea.cpp \
    Agente/Taticas/MarcarAreaAdv.cpp

CONFIG   += console link_pkgconfig

PKGCONFIG += opencv
QMAKE_CXXFLAGS += -O3 -frounding-math

LIBS += -L/usr/lib -lCGAL -lboost_system -lboost_thread -lprotobuf

## Para teste do navegador
#LIBS += `allegro-config --libs`
