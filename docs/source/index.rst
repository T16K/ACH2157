Bem vindo à documentação PROTETOR SOLAR ☀️
=============================================

O que é isso?
-------------

Esse é o projeto final da **Disciplina: ACH2157 - Computação Física e Aplicações**: https://github.com/FNakano/CFA

Nele está sendo proposto o uso do aplicativo *PROTETOR SOLAR ☀️**, como uma forma mais acessível do *UV Camera for Sunscreen Test*. O objetivo é que o usuário seja alertado pelo aplicativo, para repassar seu protetor solar conforme seu contexto.

Inspiração
^^^^^^^^^^

Ao olhar para o Objetivo de Desenvolvimento Sustentável 3. **Assegurar uma vida saudável e promover o bem-estar para todas e todos, em todas as idades**, foi pensado uma forma de promover o alinhamento específico do **3.4** - Até 2030, reduzir em um terço a mortalidade prematura por doenças não transmissíveis via prevenção e tratamento, e promover a saúde mental e o bem-estar.

Para isso, foi decidido incentivar à adoção de um novo hábito saudável e ajudar o usuário à manter-lo. Por exemplo, todos já passaram pela situação de começar o ano, com objetivos e planos bem estruturados, mas com o passar dos meses desistir deles. Esse *clássico* tipo de atitude que será superado pelo usuário.

Então, ao começar por uma rotina simples de cuidados com a pele está sendo oferecido ao usuário, a possibilidade dele, de criar seu hábito de passar o protetor o solar em momentos importantes, para isso o aplicativo tem a função de auxiliar e facilitar esse aprendizado.

Referência para o conceito de hábito: https://sites.google.com/view/sources-change/

Como funciona?
^^^^^^^^^^^^^^

Esta seção foi dividindo em duas partes, a primeira será dos objetos físicos que serão responsáveis por avaliar o contexto do usuário, e a segunda que são os programas para interpretar esse contexto e devolver uma decisão.

.. figure:: ../../img/esquema.png

Os Componentes
--------------

.. toctree::
    :maxdepth: 1

    comp/esp
    comp/sensor
    comp/bateria

Os *Softwares*
--------------

.. toctree::
    :maxdepth: 1

    software/programa
    software/aplicativo
    software/iot
    software/ide

Referências
^^^^^^^^^^^

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/
https://docs.micropython.org/en/latest/esp32/quickref.html
