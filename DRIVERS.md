# Drivers Vulkan: o que vem no app e por quê

Pesquisa de 05/11/2026 para a b14. Ela juntou três fontes:

- as issues do projeto original ([BOTWRecompAndroid](https://github.com/mamcjr/BOTWRecompAndroid/issues)), onde jogadores contam qual driver rodou este jogo em qual celular;
- os repositórios de drivers mais usados, com a data e a quantidade de downloads de cada versão;
- guias de emulação de 2026.

Todos os pacotes foram baixados das páginas de versões dos próprios autores e conferidos por dentro: são para arm64, têm as funções que o motor usa e reconhecem as GPUs da aba em que estão. A soma SHA-256 de cada um está em `android/botwrecompandroid/app/src/drivers/LEIA-ME.txt`.

**Nenhum foi testado neste jogo fora do Galaxy S23 Ultra.** Para outros celulares, a recomendação vem do que os jogadores relataram.

## Como o app escolhe

Na primeira vez que o app abre, ele identifica o celular:

- a marca e o sistema (One UI, HyperOS, ColorOS...);
- o chip (por exemplo, SM8550);
- a GPU;
- a versão do driver do próprio sistema (por exemplo, 676.79).

Com isso, ele escolhe o driver recomendado para aquele aparelho. Depois disso, vale a escolha do jogador.

Na tela de drivers (Configurações > Arquivos > Driver Vulkan), cada chip tem uma aba. A aba do seu chip já vem aberta, com o driver mais novo em cima. Um driver só é copiado para o celular quando você escolhe, então os outros não ocupam espaço.

**A versão S23 só traz a aba do Snapdragon 8 Gen 2.** A versão Universal traz todas.

### O ajuste do 8 Gen 2 (One UI)

Algumas versões do driver do sistema do Adreno 740 usam um ajuste de memória da GPU. O driver Turnip precisa usar o mesmo ajuste; se não usar, a tela pisca. A versão "One UI" do Turnip liga esse ajuste.

O que decide é a versão do driver do sistema, não a marca:

| Celular | Versão do driver do sistema | Precisou do ajuste? |
|---|---|---|
| Galaxy S23 Ultra | 676.79 | sim |
| OnePlus 12R | 676.71 | sim ([relato](https://github.com/Droid-Deck/DroidDeck/issues/1392)) |
| AYN Thor | 676.53 | não |

Por isso, o app recomenda a versão One UI em celulares Samsung e em qualquer 8 Gen 2 com o driver do sistema na versão 676.70 ou mais nova.

## Recomendados por chip

| Aba | Recomendado | Por quê |
|---|---|---|
| 8 Gen 2 (Adreno 740) | Banners Turnip 27.0.0 de 25/10, One UI ou padrão (veja acima) | Testado neste jogo no S23 Ultra |
| 8 Gen 3 (Adreno 750) | K11MCH1 Turnip 26.0.0 R8 | Relatado rodando este jogo num Honor (issue #41) |
| 8 Gen 1 e 8+ Gen 1 (Adreno 730) | K11MCH1 Turnip 26.0.0 R8 | Indicado para o 730 por guias. No 8+ Gen 1, o Gen8 V38 chamou a GPU de "725" (issue #31): use um de 7xx |
| 7+ Gen 2 (Adreno 725) | Vauzi 710/720/722 4.5 | Num Poco F5 foi o único acima de 15 FPS neste jogo (issue #21) |
| 8s Gen 3 e 7+ Gen 3 (735, 732) | StevenMXZ Gen8 V38 Patched | Jogado num Poco F6 (issues #159 e #168). A 26.3.0 R6 rodou no 732 (issue #103) |
| 710, 720 e 722 | o driver do sistema | No Adreno 710, o do sistema rodou de 3 a 6 FPS mais rápido que o Turnip (issue #144) |
| Adreno 6xx (888, 865, 845...) | K11MCH1 Turnip 24.3.0 R9v2 | O driver do sistema não tem o que o jogo precisa (issues #5 e #6). A R9v2 rodou no 888 (issue #58) |
| Adreno 8xx (8 Elite, 8s Gen 4) | StevenMXZ Gen8 V38 | Cerca de 30 FPS num Poco F7 (issue #212) |
| Adreno 840 (8 Elite Gen 5) | whitebelyash A8xx V29 | Com o V38 a imagem ficou avermelhada; o V29 resolveu (issue #32) |

Os números das issues são do [projeto original](https://github.com/mamcjr/BOTWRecompAndroid/issues).

## Todos os drivers e de onde vêm

| Autor | Página | Drivers no app |
|---|---|---|
| The412Banner | [Banners-Turnip](https://github.com/The412Banner/Banners-Turnip) | 27.0.0 r5 de 05/11 (padrão, One UI, 710/720, A8xx e AIO) e os dois de 25/10, testados |
| StevenMXZ | [Adreno-Tools-Drivers](https://github.com/StevenMXZ/Adreno-Tools-Drivers) | 27.0.0 R1 (padrão e One UI), Gen8 V38, Gen8 V38 Patched e 26.3.0 R6 |
| K11MCH1 (Kimchi) | [AdrenoToolsDrivers](https://github.com/K11MCH1/AdrenoToolsDrivers) | 26.0.0 R8, 24.3.0 R9v2 e 24.1.0 R18 (a6xx) |
| MrPurple666 | [purple-turnip](https://github.com/MrPurple666/purple-turnip) | T30 |
| nihui | [mesa-turnip-android-driver](https://github.com/nihui/mesa-turnip-android-driver) | Mesa 26.2.6 oficial |
| Vauzi | [710](https://github.com/Vauzi-17/710) | 710/720/722 4.5 e 4.5.1 |
| sherft2607 | [turnip-adreno722-duo](https://github.com/sherft2607/turnip-adreno722-duo) | Duo 5.1 (Adreno 722) |
| whitebelyash | [freedreno_turnip-CI](https://github.com/whitebelyash/freedreno_turnip-CI) | A8xx V29 e V32 |
| faux123 | [turnip-faux123-driver](https://github.com/faux123/turnip-faux123-driver) | 1.2.5 (Adreno 8xx) |
| AlexSanz0902 | [turnip-sd865-z](https://github.com/AlexSanz0902/turnip-sd865-z) | TurnipZ 0.3.0 (Adreno 6xx) |
| Balemuni | [Balemunis-Aurora](https://github.com/Balemuni/Balemunis-Aurora) | Apex 2 Ultimate (8 Gen 2) e Universal |

Os dois do Balemuni vinham sem compressão (14 MB cada). Aqui eles foram comprimidos de novo, com o mesmo conteúdo.

Todos são o driver Turnip da [Mesa](https://docs.mesa3d.org/license.html), sob a licença MIT e outras.

## O que ficou de fora

- **Drivers da Qualcomm** (v762, v8xx...): são proprietários e não podem ser redistribuídos. Quem quiser usa o botão **Adicionar driver** com o .zip baixado do [K11MCH1](https://github.com/K11MCH1/AdrenoToolsDrivers/releases) ou do [StevenMXZ](https://github.com/StevenMXZ/Adreno-Tools-Drivers/releases).
- **Versões repetidas:** o Banners sai várias vezes por dia, então só a mais nova entrou.
- **Drivers para Mali (Samsung Exynos, MediaTek):** não usam Turnip.

## Ajude a melhorar a lista

Testou um driver no seu celular? Abra uma issue com estas informações, e a recomendação passa a usar o seu resultado:

- o modelo do celular;
- o chip;
- o driver usado;
- o FPS;
- se apareceu algum defeito na imagem.

---

# Vulkan drivers: what comes in the app and why (English summary)

Research of 2026-11-05 for b14: the original project's issues (which driver ran this game on which phone), the driver repositories (dates, downloads) and 2026 emulation guides.

On its first start the app reads the phone's chip, GPU and system driver version and picks the recommended driver. Afterwards the player's choice stays. Each chip has a tab, newest driver at the top, and a driver is copied out only when it's chosen. The S23 version only has the Snapdragon 8 Gen 2 tab; the Universal one has them all.

**Only the Galaxy S23 Ultra was tested on this game.** Everything else follows player reports.

**8 Gen 2:** the One UI build matches the Adreno 740 flag that newer system drivers set; without it the screen flickers. The app uses it on Samsung phones and on any 8 Gen 2 whose system driver is 676.70 or newer.

**Recommended by chip:**

| Chip | Recommended driver |
|---|---|
| 8 Gen 2 | Banners 27.0.0 of 10/25: One UI or standard, as above (tested) |
| 8 Gen 3 and 8 Gen 1 | K11MCH1 26.0.0 R8 |
| 7+ Gen 2 | Vauzi 4.5 |
| 8s Gen 3 and 7+ Gen 3 | StevenMXZ Gen8 V38 Patched |
| Adreno 710/720/722 | the system driver |
| Adreno 6xx | K11MCH1 24.3.0 R9v2 |
| Adreno 8xx | StevenMXZ Gen8 V38 |
| Adreno 840 | whitebelyash A8xx V29 |

**Not included:** Qualcomm's proprietary drivers, which can't be redistributed. Add them with **Add driver**.
