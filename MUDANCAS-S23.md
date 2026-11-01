# O que mudou em relação ao original

Ponto de partida: BOTWRecompAndroid `0.2.3-beta`, de [mamcjr](https://github.com/mamcjr/BOTWRecompAndroid). A versão de
cada etapa está no histórico do repositório.

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

## O que não foi modificado

- As ferramentas de compilação no celular e a identificação do código do jogo: `gen.id` e `GAMELIB_ID` são os mesmos
  desde a b2, então atualizar entre estas versões não recompila o jogo.
- Saves e arquivos do jogo: nada disso faz parte do repositório.
