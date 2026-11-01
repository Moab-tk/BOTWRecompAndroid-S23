# BOTW S23

Modificação **não oficial** do [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid), ajustada para o
**Samsung Galaxy S23 Ultra** (Snapdragon 8 Gen 2, Adreno 740).

> [!IMPORTANT]
> **Todo o crédito do projeto é de [mamcjr](https://github.com/mamcjr), autor do BOTWRecompAndroid, e de
> [peiikai](https://github.com/peiikai), autor do LAS Recomp, de onde tudo parte.** Esta versão é só uma modificação
> feita com IA a partir das ideias de uma pessoa. Não é feita nem tem suporte dos autores originais, então não leve
> problemas daqui até eles.

> [!NOTE]
> Não leve nada a sério. Se não der certo no seu celular, é só deixar para lá e baixar a versão que achar melhor.

O texto original do projeto, com todos os detalhes técnicos, está em [README-ORIGINAL.md](README-ORIGINAL.md). A lista
do que foi modificado está em [MUDANCAS-S23.md](MUDANCAS-S23.md).

## Sem arquivos do jogo

**Nenhum arquivo do jogo vem incluído.** Você precisa do seu próprio dump, obtido legalmente, de *Breath of the Wild*
(`exefs` e `romfs`, extraídos). Não serão dadas instruções de como obtê-lo.

## O que esta versão tem de diferente

- **Compilada para o processador do S23**, sem as instruções que ele não tem.
- **Instala ao lado do original:** o pacote é outro (`com.botwrecomp.android.s23`), então uma versão não substitui a
  outra.
- **Dois drivers Turnip já no aplicativo**, em Configurações > Arquivos > Driver Vulkan, com o indicado para o seu
  celular marcado como Recomendado.
- **Configurações recomendadas com um toque**, as mesmas testadas no S23 Ultra.
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

Esses são os valores que o botão aplica:

| Opção | Valor |
|---|---|
| Limite de quadros | 30 FPS |
| Resolução interna | 1x |
| Resolução de saída | 900 linhas |
| Ampliação da imagem | FSR 1 |
| Suavização | Desligada |
| Código do jogo | Nativo |
| Apresentação | FIFO |
| Quadros regulares a 30 FPS | Ligado |
| Compatibilidade do driver | Tudo ligado |
| Driver | Turnip recomendado para o seu celular |

O formato da tela, o som, os controles, os mods e os saves não mudam.

## Qual driver usar

Os dois vêm da mesma versão (`v27.0.0-20261025-r5`, de
[The412Banner](https://github.com/The412Banner/Banners-Turnip)), feita a partir do Mesa.

| Seu celular | Driver |
|---|---|
| Galaxy S23, com One UI | `Turnip-v27.0.0-20261025-r5-8G2-OneUI` |
| Outro Snapdragon 8 Gen 2 | `Turnip-v27.0.0-20261025-r5` |
| Outras GPUs Adreno 6xx e 7xx | `Turnip-v27.0.0-20261025-r5`, sem garantia |

O de One UI pode fazer a tela piscar em celulares que não são Samsung. Em outros aparelhos, nada aqui foi testado.

## Desempenho medido

Estes números são de um único aparelho e não são promessa. Nas partidas abaixo: S23 Ultra, jogo na versão 1.8.2, código
nativo, 30 FPS, resolução 1x. Até a b7, a saída era de 900 linhas; na b8, de 1080, com a proporção original.

| Medição | FPS médio | Medições abaixo de 29 FPS | Picos de 100 ms ou mais |
|---|---:|---:|---:|
| b6: 10 minutos em lugares variados | 29,9 | 6 de 290 | 1 |
| Etapa da b7: 11 minutos em áreas nunca visitadas | 29,9 | 5 de 341 | 5 |
| b8: 4 minutos e meio | 29,9 | 6 de 120 | 4 |

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
> Essas partidas foram feitas com **cooler no celular** e com o **limitador térmico do sistema desativado pelo dono do
> aparelho**, por ferramentas de terceiros. Isso não faz parte do app e não é recomendado aqui: desativar a proteção
> térmica é por sua conta e risco. O chip passou de 80 °C. Sem cooler, espere menos desempenho.

## Problemas conhecidos

- **Paredes verticais no terreno ("cortinas"):** o chão pode virar paredes ou picos esticados, principalmente depois da
  cena de ativar uma Torre Sheikah. O defeito vem do projeto original e aparece com qualquer driver. Esta versão tem
  uma tentativa de correção: nos testes da b8, o defeito não apareceu num lugar onde costumava aparecer, mas isso ainda
  não é confirmação. Se acontecer, carregue um save feito depois.
- **Engasgadas em áreas novas:** na primeira visita, um shader pode levar de 250 a 300 ms para ficar pronto. Depois ele
  fica guardado no celular, então as próximas visitas tendem a ser mais leves.
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

Em Configurações > Arquivos > Testes há opções que vêm desligadas: manter a GPU acordada, modo de apresentação, núcleos
para shaders, filtro anisotrópico e modo do Turnip. Teste uma por vez e salve um bloco antes. **Manter a GPU acordada**
não teve ganho comprovado e, se o sistema fechar o app à força, pode continuar ligada até você abrir o app de novo ou
reiniciar o celular.

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
