# BOTW S23

**Português** | [English](README.en.md)

Modificação **não oficial** do [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid), ajustada para o
**Samsung Galaxy S23 Ultra** (Snapdragon 8 Gen 2, Adreno 740).

> [!IMPORTANT]
> **O projeto original é de [mamcjr](https://github.com/mamcjr), criador do
> [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid), a partir do LAS Recomp de
> [peiikai](https://github.com/peiikai). Todo o crédito do projeto é deles.**
>
> Esta versão é uma modificação pessoal feita por outra pessoa, com ajuda de IA. mamcjr deu autorização para publicar,
> mas não participou destas mudanças, não as testou e não responde por elas.

> [!CAUTION]
> **Problema nesta versão? Abra uma [issue aqui](https://github.com/Moab-tk/BOTWRecompAndroid-S23/issues). Nunca leve estas reclamações ao projeto original.**
> Um erro nesta versão pode ter sido criado por estas modificações e pode não existir no original. Ela pode funcionar
> bem no celular de quem testou e funcionar mal no seu.

> [!NOTE]
> Não leve nada a sério. Se não der certo no seu celular, é só deixar para lá e baixar a versão que achar melhor.

> [!WARNING]
> **O celular dos testes é modificado.** É um S23 Ultra de 12 GB, um aparelho já forte, com overclock, com o limitador
> térmico do sistema desativado por ferramentas de terceiros, com outras modificações que melhoram levemente o desempenho
> e com cooler. Nenhum número desta página vale como promessa para um celular comum. No meu teste pessoal, esta versão
> teve ganho real de desempenho e de fluidez nesse aparelho. Fica para outras pessoas testarem como ela se sai em celulares
> sem modificação.

O texto original do projeto, com todos os detalhes técnicos, está em [README-ORIGINAL.md](README-ORIGINAL.md). A lista
do que foi modificado está em [MUDANCAS-S23.md](MUDANCAS-S23.md).

## Sem arquivos do jogo

**Nenhum arquivo do jogo vem incluído.** Você precisa do seu próprio dump, obtido legalmente, de *Breath of the Wild*
(`exefs` e `romfs`, extraídos). Não serão dadas instruções de como obtê-lo.

## O que esta versão tem de diferente

- **Compilada para o processador do S23**, sem as instruções que ele não tem.
- **Instala ao lado do original:** o pacote é outro (`com.botwrecomp.android.s23`), então uma versão não substitui a
  outra.
- **Baseada na versão 0.2.13 do original**, com as correções de mamcjr até ela, como os ícones de ação nos controles
  na tela.
- **Duas versões:** a S23, feita para o processador do Snapdragon 8 Gen 2, e a Universal, para qualquer celular arm64
  com Vulkan. A Universal é experimental: só foi testada no S23.
- **Menos objetos sumindo ao entrar nas áreas:** o app lembra os pipelines que o jogo usou e monta de novo antes do primeiro
  desenho. Ao entrar no mundo, os desenhos pulados caíram de 5.780 para 132.
- **Cinco drivers Turnip já no aplicativo**, em Configurações > Arquivos > Driver Vulkan. Os dois testados aparecem como
  Recomendado, e os três mais novos aparecem como não testados neste jogo.
- **Configurações recomendadas com um toque:** as testadas no S23 Ultra e uma opção mais leve para o S23, o S23+ e
  celulares mais fracos.
- **Configurações salvas:** 8 blocos para guardar tudo o que você ajustou e voltar quando um teste piorar.
- **Interface maior e mais fácil de tocar:** escolha de tamanho do texto, nomes longos que deslizam, opções em cartões.
- **Quadros regulares a 30 FPS:** a tela fica em 60 Hz e cada quadro segue o ritmo real dela. Nas medições, 97% dos
  quadros apareceram no tempo certo, sem nenhum descartado.
- **Menos risco de travar em sessões longas**, com tabelas de shaders maiores. A lista completa está em
  [MUDANCAS-S23.md](MUDANCAS-S23.md).

## Instalando

Você precisa de Android 11 ou mais novo, de um celular arm64 com Vulkan e de cerca de 30 GB livres por versão do jogo.

1. Baixe o APK na aba **Releases** desta página e instale.
2. Abra, entre em **Configurar arquivos do jogo** e escolha a pasta com o seu `exefs` e `romfs`.
3. Espere terminar. Na primeira vez, o celular pode demorar e esquentar.
4. Na tela inicial, abra **Configurações salvas** e toque em **Usar configurações recomendadas**.
5. Confirme. O app reinicia e o jogo está pronto para jogar.

Atualizando uma versão anterior desta modificação, basta instalar por cima: os saves e as configurações continuam.

## Configurações recomendadas

Esses são os valores que os botões aplicam. A opção mais leve não foi testada no S23, no S23+ nem em celulares mais
fracos.

| Opção | S23 Ultra | S23, S23+ e mais fracos |
|---|---|---|
| Limite de quadros | 30 FPS | 30 FPS |
| Resolução interna | 1x | 75% |
| Resolução de saída | 1080 linhas | 900 linhas |

As duas usam os mesmos valores abaixo:

| Opção | Valor |
|---|---|
| Ampliação da imagem | FSR 1 |
| Suavização | Desligada |
| Código do jogo | Nativo |
| Apresentação | FIFO |
| Quadros regulares a 30 FPS | Ligado |
| Compatibilidade do driver | Automático (ligado na Adreno 740) |
| Driver | Turnip recomendado para o seu celular |

O formato da tela, o som, os controles, os mods e os saves não mudam.

## Qual driver usar

Todos são builds do Mesa feitas por [The412Banner](https://github.com/The412Banner/Banners-Turnip). Os de 25/10 foram os
usados nos testes. Os de 01/11 são builds automáticas: o próprio autor avisa que não foram testadas em aparelho, e elas
não foram testadas neste jogo.

| Seu celular | Driver | Situação |
|---|---|---|
| Galaxy S23, com One UI | `Turnip-v27.0.0-20261025-r5-8G2-OneUI` | Recomendado |
| Outro Snapdragon 8 Gen 2 | `Turnip-v27.0.0-20261025-r5` | Recomendado |
| Galaxy S23, com One UI | `Turnip-v27.0.0-20261101-r4-8G2-OneUI` | Mais novo, não testado |
| Outras GPUs Adreno 6xx e 7xx | `Turnip-v27.0.0-20261101-r4` | Mais novo, não testado |
| Adreno 8xx (Snapdragon 8 Elite) | `Turnip-v27.0.0-20261101-r4-A8xx` | Experimental, não testado |

O de One UI pode fazer a tela piscar em celulares que não são Samsung. Em outros aparelhos, nada aqui foi testado.

## Desempenho medido

Estes números são de um único aparelho **modificado** e não são promessa: S23 Ultra de 12 GB, com overclock e outras
modificações, jogo na versão 1.8.2, código nativo, 30 FPS, resolução 1x. Até a b7, a saída era de 900 linhas; na b8, de
1080, com a proporção original.

| Medição | FPS médio | Medições abaixo de 29 FPS | Picos de 100 ms ou mais |
|---|---:|---:|---:|
| b6: 10 minutos em lugares variados | 29,9 | 6 de 290 | 1 |
| Etapa da b7: 11 minutos em áreas nunca visitadas | 29,9 | 5 de 341 | 5 |
| b8: 4 minutos e meio | 29,9 | 6 de 120 | 4 |

Na b9, parado no mesmo lugar e no mesmo save da b8, com o celular carregando: 29,9 FPS contra 29,8; 93,7% dos quadros no
tempo certo contra 90,8%; e 84,4 °C no processador contra 86,8 °C.

Na b10, duas sessões seguidas, no mesmo save e no mesmo caminho, com o controle de temperatura ligado:

| | Só anotando | Montando antes |
|---|---:|---:|
| FPS médio | 29,8 | 29,7 |
| Pico ao entrar no mundo | 305 ms | 213 ms |
| Desenhos pulados ao entrar no mundo | 5.780 | 132 |
| Desenhos pulados por minuto | 461 | 106 |

O chip ficou entre 70 e 76 °C e a bateria entre 29 e 31 °C. A queda de FPS logo depois de entrar no mundo, vista nessa
medição, foi corrigida depois dela e a correção não foi medida.

Cada medição cobre 2 segundos de jogo. O FPS médio não conta tudo: ele mostra quantos quadros saíram, não se chegaram à
tela no ritmo certo. Isto foi medido pelo próprio sistema, em cada quadro mostrado:

| Na tela | b7 | b8 |
|---|---:|---:|
| Quadros no tempo certo | 93,3% | 97,2% |
| Quadros descartados por segundo | 1,0 | 0 |
| Quadros atrasados por segundo | 1,0 | 0,45 |
| Variação do ritmo | 8,6 ms | 4,6 ms |

**O que não funcionou:** 40 FPS (média de 36,8, com a GPU perdendo velocidade pelo calor, e 88 °C no processador) e a
distância de visão reduzida do próprio jogo no mapa inteiro (3,5% menos desenhos, no mesmo lugar, sem mudar o uso da
GPU).

> [!WARNING]
> Essas partidas foram feitas com **overclock**, com **cooler no celular** e com o **limitador térmico do sistema
> desativado pelo dono do aparelho**, por ferramentas de terceiros. Nada disso faz parte do app, e nada disso é recomendado
> aqui: fazer essas modificações é por sua conta e risco. O chip passou de 80 °C. Sem essas modificações, espere menos
> desempenho.

## Problemas conhecidos

- **Paredes verticais no terreno ("cortinas"):** mamcjr corrigiu este defeito na 0.2.10, e a correção está aqui. Ela ainda
  não foi testada a fundo no S23. Se acontecer, carregue um save feito depois.
- **Engasgadas em áreas novas:** na primeira visita, um shader pode levar de 250 a 300 ms para ficar pronto. Depois ele
  fica guardado no celular, então as próximas visitas tendem a ser mais leves.
- **Montagem antecipada:** a primeira sessão depois de instalar uma versão nova só anota os pipelines. O ganho aparece da
  segunda em diante. Logo depois de entrar no mundo, essa montagem ainda pode ocupar um pouco do processador.
- **Versão Universal:** só foi testada no S23. Em outros celulares, nada foi conferido.
- **Calor:** mesmo com cooler, o chip passou de 70 °C e o Android marcou o celular como muito quente. O controle de
  temperatura baixou a imagem em degraus, como deve.
- **GPU presa em frequência baixa:** em algumas partidas, o sistema baixou a GPU de 719 para cerca de 300 MHz e só soltou
  com o jogo fechado, mesmo com o chip a 60 °C. Nas duas vezes medidas, a ferramenta que desativa o limitador não estava
  rodando. Se o jogo ficar lento de repente, feche e abra.
- **S23 e S23+ não foram testados.** Num celular de 12 GB, o jogo ocupou cerca de 5 GB de RAM. Desligar a memória da GPU
  nas opções de compatibilidade economizou cerca de 1 GB numa medição curta, mas esquentou mais, ficou mais irregular e
  o jogo fechou sozinho uma vez, com uma falha ainda sem causa conhecida.
- **Testada em um celular só.** Em outro aparelho, tudo pode ser diferente.
- **Proporção da tela:** há relato de defeito em tela cheia e em 16:9, ainda sem causa encontrada.
- **Geração de quadros (Lossless Scaling):** foi testada e retirada, porque no S23 os quadros reais caíram para 15 a 23
  FPS. Esta versão não tem essa opção.

## Opções de teste

Na tela inicial, em Configurações > Vídeo > Testes, há opções que vêm desligadas: manter a GPU acordada, modo de apresentação, núcleos
para shaders, filtro anisotrópico e modo do Turnip. Teste uma por vez e salve um bloco antes. **Manter a GPU acordada**
não teve ganho comprovado e, se o sistema fechar o app à força, pode continuar ligada até você abrir o app de novo ou
reiniciar o celular.

## Apoie, se quiser

Se esta versão funcionou para você e quiser ajudar com os custos, como os tokens do Claude, uma ajuda voluntária é
bem-vinda.

A doação é opcional e não dá nenhum benefício: nada de recursos, prioridade, suporte ou versão especial. Ela vai para
Moab, autor desta modificação, e não para mamcjr, peiikai ou a Nintendo. Para apoiar o projeto original, use o botão
**Sponsor** do [repositório de mamcjr](https://github.com/mamcjr/BOTWRecompAndroid).

Pix (chave aleatória): `5eb148c4-81dc-47cd-b2cc-b3171d3c06ab`

## Compilando

Os passos são os do projeto original, em [README-ORIGINAL.md](README-ORIGINAL.md). O release usa uma chave própria, que
fica fora do repositório em `~/.botwrecompandroid/keystore.properties`. Sem ela, compile a versão de depuração.

## Créditos

- **[mamcjr](https://github.com/mamcjr)**, pelo [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid) e pelo
  [LASRecompAndroid](https://github.com/mamcjr/LASRecompAndroid): esta modificação existe por causa desse trabalho.
- **[peiikai](https://github.com/peiikai)**, pelo [LAS Recomp](https://github.com/peiikai/LASRecomp) (licença MIT), o
  recompilador e o motor de onde tudo parte.
- [Revivedx](https://github.com/Revivedx), pelo [SavageWindRecomp](https://github.com/Revivedx/SavageWindRecomp);
  [Nycolazs](https://github.com/Nycolazs), pelo LASRecomp-Android-Plus; a decompilação
  [zeldaret/botw](https://github.com/zeldaret/botw) e o [open-ead/sead](https://github.com/open-ead/sead).
- [tib-kpl](https://github.com/tib-kpl/BOTWRecompAndroid), pela correção das páginas de comando trazida para a b4.
- [The412Banner](https://github.com/The412Banner/Banners-Turnip), pelas versões do driver, e o projeto
  [Mesa](https://www.mesa3d.org), pelo driver Turnip.
- [AMD FSR 1](https://github.com/GPUOpen-Effects/FidelityFX-FSR),
  [Snapdragon GSR](https://github.com/SnapdragonStudios/snapdragon-gsr), [SMAA](https://github.com/iryoku/smaa) e
  [libadrenotools](https://github.com/bylaws/libadrenotools). As demais bibliotecas e licenças estão em
  [README-ORIGINAL.md](README-ORIGINAL.md).
- Modificações feitas com o [Claude Code](https://claude.com/claude-code) (Anthropic), dirigidas e testadas por uma
  pessoa.

*The Legend of Zelda* e *Breath of the Wild* são marcas da Nintendo. Este projeto não é afiliado nem endossado pela
Nintendo. A licença do código está em [LICENSE](LICENSE); os componentes de terceiros mantêm as licenças deles.
