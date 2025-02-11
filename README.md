# PWM
## Link vídeo:
https://youtu.be/2uyPexGN7wo?feature=shared

---

# Projeto: Controle de Servomotor por PWM

## Descrição
Este projeto implementa o controle de um servomotor utilizando o microcontrolador RP2040 (Raspberry Pi Pico W) e o módulo PWM (Pulse Width Modulation). O servomotor é posicionado em ângulos específicos (0°, 90° e 180°) e, em seguida, realiza uma movimentação suave entre esses ângulos. O projeto também integra um LED RGB para fornecer feedback visual durante a movimentação do servomotor.

O código está localizado no arquivo `PWM.c`.

---

## Como Rodar o Projeto

### 1. Clone o repositório:
```bash
git clone https://github.com/Daniel24060/PWM.git
```

### 2. Entre na pasta do projeto:
```bash
cd PWM
```

---

## Instruções para Configuração e Compilação do Projeto

### Passo 1: Baixar o Ninja
Acesse a página oficial de releases do Ninja: [Ninja Releases no GitHub](https://github.com/ninja-build/ninja/releases).

- Baixe o arquivo binário mais recente para Windows (geralmente um `.zip`).
- Extraia o conteúdo do arquivo `.zip` (haverá um arquivo `ninja.exe`).

### Passo 2: Adicionar o Ninja ao Path do sistema
Para que o Ninja seja reconhecido como um comando em qualquer terminal, siga estas etapas:

1. Clique com o botão direito no botão Iniciar e selecione **Configurações**.
2. Vá em **Sistema → Sobre → Configurações avançadas do sistema** (no lado direito).
3. Na aba **Avançado**, clique em **Variáveis de Ambiente**.
4. Na seção **Variáveis do Sistema**, localize a variável `Path` e clique em **Editar**.
5. Clique em **Novo** e adicione o caminho completo para o diretório onde você extraiu o `ninja.exe`, por exemplo:
   ```
   C:\Users\SeuUsuario\Downloads\ninja-win
   ```
6. Clique em **OK** em todas as janelas.

### Passo 3: Verificar se o Ninja está funcionando
Abra um terminal (PowerShell ou Prompt de Comando) e digite o comando abaixo para verificar a instalação:
```bash
ninja --version
```

### Passo 4: Configurar e Compilar o Projeto
Volte ao diretório do projeto e abra um terminal.

1. Crie ou limpe a pasta `build`:
   ```bash
   rmdir /s /q build
   mkdir build
   cd build
   ```

2. Configure o projeto com o CMake:
   ```bash
   cmake -G Ninja ..
   ```

3. Compile o projeto:
   ```bash
   ninja
   ```

Após isso, o arquivo `main.elf` será gerado na pasta `build`.

---

## Simulação no Wokwi
Após a configuração, você pode usar o simulador Wokwi para testar o circuito.

1. Acesse o simulador através do link: [Wokwi](https://wokwi.com/).
2. Ou use a extensão do Wokwi no VSCode: [Wokwi VSCode](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode).

### Como Funciona a Simulação
- O servomotor é controlado pelo sinal PWM gerado pelo RP2040.
- O LED RGB muda de cor conforme o servomotor se move:
  - **Vermelho**: Servomotor em 0°.
  - **Verde**: Servomotor em 90°.
  - **Azul**: Servomotor em 180°.
- Durante a movimentação suave, o LED faz uma transição de cores entre vermelho e azul.

Após configurar o ambiente, inicie a simulação no Wokwi integrado ao VS Code.

---

## Requisitos da Tarefa

### 1. Configuração do PWM na GPIO 22 com frequência de 50Hz (período de 20ms)
- O PWM é configurado com um período de 20ms (50Hz) usando a função `pwm_config_set_wrap`.

### 2. Ciclo ativo de 2.400µs (0,12%) para posicionar o servomotor em 180°
- O ciclo ativo é definido como 2400µs, e o código aguarda 5 segundos nessa posição.

### 3. Ciclo ativo de 1.470µs (0,0735%) para posicionar o servomotor em 90°
- O ciclo ativo é definido como 1470µs, e o código aguarda 5 segundos nessa posição.

### 4. Ciclo ativo de 500µs (0,025%) para posicionar o servomotor em 0°
- O ciclo ativo é definido como 500µs, e o código aguarda 5 segundos nessa posição.

### 5. Movimentação periódica suave entre 0° e 180°
- O servomotor é movido suavemente entre 0° e 180° com incrementos de 5µs e um atraso de 10ms entre cada ajuste.

### 6. Integração com o LED RGB (GPIO 12)
- O LED RGB muda de cor conforme o servomotor se move, fornecendo feedback visual.

---

## Autor
- **Daniel24060**

---

## Licença
Este projeto está licenciado sob a licença MIT. Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.

---
