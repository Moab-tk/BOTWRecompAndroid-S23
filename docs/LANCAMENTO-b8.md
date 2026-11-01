# BOTW S23 b8

Modificação **não oficial** do [BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid), para o Samsung Galaxy
S23 Ultra. Todo o crédito do projeto é de mamcjr e peiikai. Isto é só uma modificação feita com IA a partir das ideias
de uma pessoa. Não leve nada a sério: se não der certo, é só deixar para lá e baixar a versão que achar melhor.

**Nenhum arquivo do jogo vem incluído.** Você precisa do seu próprio dump, obtido legalmente.

## Novidades

- **Quadros regulares a 30 FPS:** a tela fica em 60 Hz e cada quadro segue o ritmo real dela. Antes, o contador marcava
  30 FPS, mas cerca de 1 quadro por segundo era descartado. Vem ligado e pode ser desligado em Configurações > Arquivos.
- **Som na primeira abertura:** quando o canal de som falha ao iniciar, o jogo tenta de novo em vez de ficar mudo. A
  falha não voltou a aparecer nos testes, então as novas tentativas ainda não foram vistas em ação.

## Medido

Um único aparelho: S23 Ultra, jogo 1.8.2, código nativo, 30 FPS, resolução 1x, saída 1080 e proporção original.

| Na tela | b7 | b8 |
|---|---:|---:|
| Quadros no tempo certo | 93,3% | 97,2% |
| Quadros descartados por segundo | 1,0 | 0 |
| Quadros atrasados por segundo | 1,0 | 0,45 |
| Variação do ritmo | 8,6 ms | 4,6 ms |

## Instalação

1. Baixe `BOTW-S23-b8.apk`, abaixo.
2. Instale. Em uma versão anterior desta modificação, basta instalar por cima: saves e configurações continuam.
3. Na primeira instalação, configure os arquivos do jogo no app.
4. Na tela inicial, abra **Configurações salvas** e toque em **Usar configurações recomendadas**.

Requisitos: Android 11 ou mais novo, celular arm64 com Vulkan e cerca de 30 GB livres por versão do jogo.

## Antes de reclamar

- Testado em um celular só, com cooler e com o limitador térmico do sistema desativado por ferramentas de terceiros.
  Isso não faz parte do app e é por conta e risco de quem fizer.
- Num celular de 12 GB, o jogo ocupou cerca de 5 GB de RAM. O S23 e o S23+, de 8 GB, não foram testados.
- O sistema pode prender a GPU em frequência baixa até o jogo fechar. Se o jogo ficar lento de repente, feche e abra.
- Em áreas nunca visitadas, ainda pode haver engasgadas curtas.

## Conferência do arquivo

```text
Pacote: com.botwrecomp.android.s23
Versão: 0.2.3-s23-b8 (código 35)
SHA-256: 6e1ae84e5d200c4ccef5c190d4a9ea976ead1542b08df2a35f371a0e63f43ec9
```

Detalhes em [MUDANCAS-S23.md](../MUDANCAS-S23.md).
