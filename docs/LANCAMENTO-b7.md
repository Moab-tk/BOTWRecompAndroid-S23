# BOTW S23 b7

Modificação **não oficial** do [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid), para o Samsung Galaxy
S23 Ultra. Todo o crédito do projeto é de mamcjr e peiikai. Isto é só uma modificação feita com IA a partir das ideias
de uma pessoa. Não leve nada a sério: se não der certo, é só deixar para lá e baixar a versão que achar melhor.

**Nenhum arquivo do jogo vem incluído.** Você precisa do seu próprio dump, obtido legalmente.

## Novidades

- Dois drivers Turnip já no aplicativo, com o indicado para o seu celular marcado como Recomendado.
- Botão **Usar configurações recomendadas**, em Configurações salvas.
- Quando o jogo precisa esperar um shader, ele mesmo faz a tarefa, e tabelas maiores evitam um possível travamento em
  sessões longas.
- Tentativa de corrigir as paredes verticais no terreno, ainda sem confirmação.
- Quatro correções do projeto original, incluindo árvores distantes sem luz.
- Fechada uma brecha em que outros aplicativos podiam abrir o jogo com chaves de teste.

## Removido

- Geração de quadros (Lossless Scaling). No S23, ela derrubou os quadros reais para 15 a 23 FPS.

## Instalação

1. Baixe `BOTW-S23-b7.apk`, abaixo.
2. Instale. Em uma versão anterior desta modificação, basta instalar por cima: saves e configurações continuam.
3. Na primeira instalação, configure os arquivos do jogo no app.
4. Na tela inicial, abra **Configurações salvas** e toque em **Usar configurações recomendadas**.

Requisitos: Android 11 ou mais novo, celular arm64 com Vulkan e cerca de 30 GB livres por versão do jogo.

## Antes de reclamar

- Testado em um celular só, com cooler.
- O limitador térmico do sistema estava desativado nas medições. Isso não faz parte do app e é por conta e risco de
  quem fizer.
- Em áreas nunca visitadas, ainda pode haver engasgadas curtas.
- As paredes verticais no terreno podem aparecer. Se acontecer, carregue um save feito depois.

## Conferência do arquivo

```text
Pacote: com.botwrecomp.android.s23
Versão: 0.2.3-s23-b7 (código 30)
SHA-256: d558cc213399dc3a1f11fa91369bbf58a40ca9c0ef01cf69471f826affbe6bb1
```

Detalhes em [MUDANCAS-S23.md](../MUDANCAS-S23.md).
