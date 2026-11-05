# O que mudou em relação ao original

Projeto original: [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid), de mamcjr. As versões de b1 a b8 partem
da `0.2.3-beta`, a b9 parte da `0.2.10-beta` a b10 e a b11 partem da `0.2.13-beta` e a b12 parte da `0.3.1-beta`. A versão de cada etapa está no histórico do repositório.

## Resumo por área

| Área | O que mudou |
|---|---|
| Compilação | Feita para o Snapdragon 8 Gen 2, sem SVE, com NDK r30 e CMake 3.30.4 |
| Pacote | `com.botwrecomp.android.s23`, chave própria, nome BOTW S23 |
| Ritmo de quadros | Hora marcada para mostrar cada quadro, seguindo o ritmo real da tela a 30 FPS |
| Som | Novas tentativas quando o canal de som falha ao iniciar |
| Shaders | Fila de trabalho atrás do jogo, quem espera faz a tarefa, tabelas maiores |
| Texturas | Alturas do terreno conferidas por inteiro a cada quadro |
| Interface | Tamanho do texto, letreiro, cartões, interruptores, um toque para mudar valores |
| Drivers | Lista de drivers guardados, dois incluídos no app, indicação de recomendado |
| Configurações | 8 blocos salvos e botão de configurações recomendadas |
| Segurança | Chaves de teste só com um arquivo que apenas o adb consegue criar |

## Versão por versão

### b1 e b2: base para o S23

- Compilação para o processador do Snapdragon 8 Gen 2, sem SVE.
- Pacote separado, para instalar ao lado do original.
- Chave fixa no release, para as próximas versões instalarem por cima.
- NDK r30 e CMake 3.30.4, os mesmos do original.
- Quebra de linha LF em todo o código, para os arquivos gerados baterem com o original.

### b3: ritmo de quadros

- Cada quadro pede uma hora para aparecer na tela (`VK_GOOGLE_display_timing`).
- Os fios que montam shaders passam a ter prioridade baixa e ficam fora do núcleo mais rápido.
- A Adreno 740 entra nos caminhos automáticos do Turnip, junto das Adreno 8xx.

### b4: estabilidade do ritmo

- Leitura de comandos sem trava, trazida do trabalho de tib-kpl.
- Atraso padrão de meio quadro, para responder mais rápido aos comandos.
- Aviso de taxa de quadros ao Android desligado por padrão.
- Falhas ficam registradas em `botwrecomp-crash.txt`, na pasta de dados da versão.

### b5: correções de ritmo

- A hora de cada quadro passa a acompanhar o próprio quadro, em vez de ficar em uma variável compartilhada.

A geração de quadros também entrou nessa versão, mas foi retirada na b7.

### b6: interface e configurações

- Tamanho da interface, com padrão maior no celular.
- Nomes longos deslizam sozinhos, e um toque muda o valor da opção.
- Mais altura para as opções, sem o título grande.
- Aba Arquivos reorganizada em cartões.
- Vários drivers guardados, para escolher sem importar de novo.
- Seção Testes, com tudo desligado por padrão: GPU acordada, modo de apresentação, núcleos para shaders, filtro
  anisotrópico e modo do Turnip.
- Configurações salvas na tela inicial, com 8 blocos. Cada bloco guarda opções, controles de toque, mods, botões e
  driver. Carregar um bloco reinicia o app. Os saves do jogo não entram nisso.
- Créditos no app e aviso de modificação não oficial na tela inicial.

### b7: shaders, drivers e publicação

**Shaders**

- Quando um desenho precisa esperar um shader, quem espera faz a tarefa, em vez de aguardar os núcleos lentos.
- Tabelas de programas e pipelines maiores: de 4.096 para 32.768 e de 8.192 para 65.536. Uma tabela cheia travaria o
  jogo.
- O registro passa a mostrar onde o tempo dos shaders é gasto e quais desenhos causam esperas longas.

**Defeitos gráficos**

- Texturas de altura do terreno conferidas por inteiro a cada quadro. É uma tentativa de corrigir as "cortinas", ainda
  sem confirmação.
- Quatro correções do original, de 30/10/2026:
  - valor de 8 bits arredondado, o que evita árvores distantes sem luz;
  - superfície perdida refeita no quadro seguinte, sem fechar o app;
  - memória automática para a Adreno 7xx com driver renomeado;
  - correções em vídeos da versão 1.0.0, tabelas de memória da GPU, reinício e saída.

**Drivers e configurações**

- Dois drivers Turnip incluídos no app, oferecidos em celulares Qualcomm sem trocar o driver em uso.
- Na Adreno 740, o driver certo aparece como Recomendado: One UI em aparelhos Samsung e o padrão nos outros.
- Botão **Usar configurações recomendadas**, em Configurações salvas.

**Removido**

- Geração de quadros, com o `Lossless.dll` e a biblioteca Bloodframe. No S23, ela derrubou os quadros reais para 15 a
  23 FPS. Um arquivo de configurações antigo com essas opções continua funcionando: elas só são ignoradas.

**Segurança**

- As chaves de teste passadas ao abrir o app agora exigem o arquivo `testes.txt` na pasta do app. O adb consegue
  criá-lo e outros aplicativos não. Antes, qualquer aplicativo do celular podia usar essas chaves, e algumas indicam
  bibliotecas a carregar.

### b8: ritmo na tela e som

**Ritmo**

- Sozinho, o Android deixava a tela em 30 Hz com o jogo a 30 FPS. Um quadro que perdia a atualização esperava 33 ms, e o
  seguinte passava por cima dele: cerca de 1 descartado por segundo, com o contador marcando 30.
- A tela agora fica em 60 Hz.
- O relógio do jogo e o da tela andam em velocidades um pouco diferentes (16,67 e 16,66 ms por atualização). Cada quadro
  passa a seguir o ritmo real da tela, medido pelo próprio sistema.
- Vem ligado, com o nome **Quadros regulares a 30 FPS**, em Configurações > Vídeo. Deixa os comandos um pouco mais
  atrasados, porque cada quadro é mostrado com 50 ms de folga.

**Som**

- Na primeira abertura depois de instalar, o canal de som de baixa latência podia abrir e falhar ao iniciar, e uma só
  tentativa deixava a sessão muda. Agora são 3 tentativas e depois mais 3 sem baixa latência.

**Interface**

- As opções Avançado e Testes saem de Arquivos e vão para Vídeo, na tela inicial.
- Segundo botão de configurações recomendadas, mais leve, para o S23, o S23+ e celulares mais fracos: resolução 75% e
  saída de 900 linhas. Essa opção não foi testada nesses celulares.
- A opção do S23 Ultra passa a usar saída de 1080 linhas.

**Revisão antes de publicar**

- Correção das "cortinas" da 0.2.10 de mamcjr.
- Orçamento de 30 FPS para o sistema no modo de 30 FPS, também de mamcjr: o processador não trabalha mais rápido do que
  precisa.
- A tela volta a pedir 60 Hz quando o app retorna do segundo plano.
- Quadros regulares só em celulares com tempo de exibição no driver, e só no modo de 30 FPS.
- As configurações recomendadas usam Automático nos modos do Turnip, o que é seguro em qualquer GPU.
- O atalho do driver do sistema não apaga mais os drivers guardados.
- Três drivers novos no app, marcados como não testados, e licenças dentro do APK.

### b9: junção com o original 0.2.10

- Tudo da b8, sobre a `0.2.10-beta` de mamcjr.
- Traz as correções do original até ela, como vídeos, sensor de movimento, texturas grandes e idiomas novos.
- A tabela de comandos passa a ser a do original.

### b10: junção com o original 0.2.13, revisão do código e montagem antecipada

- Tudo da b9, sobre a `0.2.13-beta` de mamcjr: ícones de ação nos controles na tela, opção de 20 FPS, folhas no chão
  corrigidas, nomes de cavalo com acento.
- **Duas versões:** a S23, compilada para o processador do Snapdragon 8 Gen 2, e a Universal, para qualquer celular arm64
  com Vulkan. Mesmo pacote: uma substitui a outra.
- **Revisão do código inteiro**, com 50 pontos anotados. Corrigidos:
  - os ícones de ação faziam o jogo fechar depois de umas 50 armas diferentes na mesma sessão (os lugares de textura do
    menu acabavam);
  - um programa de shader podia ser liberado enquanto a linha de desenho ainda usava;
  - as esperas do jogo usavam o relógio do sistema e mudavam junto com a hora do celular;
  - as configurações eram gravadas por cima do arquivo, sem cópia e sem trava: um fechamento no meio podia apagar tudo;
  - uma espera de 10 s pela GPU fechava o app no Android; agora espera mais 10 s antes de desistir;
  - o jogo aparecia por cima da tela de bloqueio sem senha (agora só com o arquivo de testes);
  - o controle de temperatura podia baixar a imagem e nunca mais subir em celulares sem sensor do chip;
  - textos das opções avançadas errados e 43 textos que apareciam em inglês.
- **Montagem antecipada de pipelines:** o app guarda quais programas e pipelines o jogo usou
  (`cache/known_pipelines.bin`). Quando o jogo carrega de novo um shader conhecido, eles são montados antes do primeiro
  desenho, numa fila de baixa prioridade feita por um ajudante só. A primeira sessão depois de instalar só anota.
- O cache de pipelines é gravado numa linha própria e não segura mais os toques a cada 30 s.
- A limpeza das vistas de textura não percorre mais a tabela inteira quando a textura não tem vistas.

### b11: cópias pela GPU e sensibilidade do toque maior

- Tudo da b10.
- **Trazido do TOTKDroid de mamcjr:**
  - cópias pequenas de buffer dentro da memória da GPU são feitas pela própria GPU, na ordem da fila; antes a linha de
    desenho parava e esperava a GPU terminar tudo (`LARECOMP_VK_GPU_BUFCOPY=0` volta ao jeito antigo);
  - as cópias de dados do jogo são reaproveitadas pelo endereço, então uma cópia maior já feita serve para as menores;
  - um registro de textura que deixa o lugar igual não espera mais a fila da linha de desenho
    (`LARECOMP_TEXREG_DRAIN_ALWAYS=1` volta ao jeito antigo).
- **Sensibilidade do toque maior**, a pedido de jogadores: o arrasto da câmera vai até 800% (era 400%) e a mira do arco
  e do arremesso, no modo de ícones, vai até 400% (era 200%). Acima de certo ponto o arrasto já inclina o direcional por
  inteiro, e a câmera não gira mais rápido que o máximo do próprio jogo.
- Testada jogando no S23 Ultra, sem medição.

### b12: junção com o original 0.3.1 e mira pelo dedo

- Tudo da b11, sobre a `0.3.1-beta` de mamcjr (traz também a 0.3.0):
  - **quedas do jogo com Magnésis, Stasis e a câmera do Slate corrigidas**;
  - com o arco puxado, um botão troca as flechas; com a runa da câmera, um botão abre o álbum; o mapa abre com dois
    toques no minimapa;
  - opção de giroscópio como a tela do Switch;
  - opção de 40 FPS em telas de 120 Hz;
  - o app pede ao Android uma folga de processador a 30 FPS;
  - correções da tela larga (luneta, câmera, minimapa, estábulo, telas de carregamento) e da viagem rápida;
  - variáveis do driver e memória por arquivo compartilhado, para Mali e Xclipse;
  - som de volta depois de deixar o app em segundo plano (a biblioteca SDL foi refeita com a correção).
- **Junção cuidadosa do ritmo dos quadros:** o original passou a alinhar os quadros com a tela de outro jeito (#183).
  Os dois jeitos leem os mesmos tempos do painel, que o driver entrega uma vez só. Os quadros regulares a 30 FPS do S23
  continuam o padrão, porque foram medidos no S23 Ultra; o ajuste do original vale quando eles estão desligados
  (`LARECOMP_VSYNC_STEER=1` ou `0` força um ou outro).
- Corrigido na junção: o original ligava a extensão de tempo de apresentação depois das duas de mapa de memória, que
  saem juntas pela contagem quando o driver recusa; o pedido de 40 FPS à janela apagava o pedido de 60 Hz dos quadros
  regulares.
- **Mira pelo dedo (experimental, desligada):** com os ícones de ação, o sensor de movimento ligado e o arco na mão,
  arrastar o dedo gira a mira como se o celular girasse, sem o limite de velocidade do direcional virtual. Fica em
  Controles, abaixo da sensibilidade da mira. `LARECOMP_DRAG_GYRO_SIGN=-1` inverte o sentido.
- **Por que a sensibilidade do arrasto parecia não mudar:** a 400% o direcional virtual já fica todo inclinado com
  quase qualquer arrasto, e a câmera não gira mais rápido que o máximo do próprio jogo. Agora a tela explica isso.
- **Escala da cena em tamanhos inteiros** (vinda do TOTK S23): o controle de temperatura e as resoluções 75% e
  dinâmica davam metades de imagem com meio ponto (por exemplo 202,5 linhas), e no TOTK isso fazia cacos nas bordas
  e o sol estourado. A escala agora é sempre múltiplo de 0,08: 90% vira 88%, 75% vira 72% (`LARECOMP_SCALE_SNAP=0`
  volta ao jeito antigo).
- **Não foi testada jogando** antes de publicar: compilada e conferida, mas o dono do aparelho de testes estava
  dormindo. A b11 continua disponível.

## O que não foi modificado

- As ferramentas de compilação no celular e a identificação do código do jogo: `gen.id` e `GAMELIB_ID` são os mesmos
  desde a b2, então atualizar entre estas versões não recompila o jogo.
- Saves e arquivos do jogo: nada disso faz parte do repositório.
