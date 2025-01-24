# Leitor de Senha com Raspberry Pi Pico W

Este é um projeto pessoal desenvolvido como parte do curso da EmbarcaTech, utilizando a plataforma BitDogLab, baseada no microcontrolador Raspberry Pi Pico W. O objetivo do projeto é criar um sistema de leitura de senha interativo que combina uma matriz de LEDs RGB 5x5, um display OLED e botões de controle.

## Funcionalidades do Sistema
- **Matriz de LEDs RGB 5x5**: Exibe números de 0 a 9 para interação do usuário.
- **Display OLED**: Mostra mensagens como instruções e confirmações de status.
- **Dois botões físicos**:
  - Botão A: Incrementa o número exibido na matriz.
  - Botão B: Salva o número atual na lista e inicia o processo de validação da senha quando o limite de entradas é atingido.
- **Validação de Senha**:
  - Verifica se os números salvos correspondem a uma senha predefinida.
  - Exibe "V" (senha correta) ou "X" (senha incorreta) na matriz de LEDs.
  - Mensagens de confirmação ou erro são exibidas no display OLED.

## Hardware Utilizado
1. **Raspberry Pi Pico W**
2. **Matriz de LEDs RGB 5x5**
3. **Display OLED (I2C)**
4. **Dois botões físicos**

## Bibliotecas Necessárias
Certifique-se de instalar as seguintes bibliotecas e dependências:
- **pico-sdk**: Para programação da Raspberry Pi Pico.
- **Bibliotecas específicas**:
  - `matrix_control.h`: Controla a matriz de LEDs RGB.
  - `matrices.h`: Contém os padrões para exibição na matriz.
  - `oled_display.h`: Gerencia o display OLED.

## Requisitos
- Conhecimento em linguagem C para sistemas embarcados.
- Configuração da plataforma BitDogLab com os componentes mencionados.

## Fluxo do Programa
1. **Inicialização**:
   - Configura os pinos dos botões, inicializa a matriz de LEDs e o display OLED.
   - Exibe a mensagem inicial "Insira a senha" no display OLED.

2. **Interação do Usuário**:
   - O botão A incrementa o número exibido na matriz (0-9).
   - O botão B salva o número atual na lista de entradas.
   - Quando a lista atinge 4 números, o sistema verifica se corresponde à senha predefinida.

3. **Validação da Senha**:
   - Se a senha for correta:
     - Exibe "V" na matriz de LEDs.
     - Mostra "Senha Aceita" no display OLED.
   - Se a senha for incorreta:
     - Exibe "X" na matriz de LEDs.
     - Mostra "Senha Errada" no display OLED.

## Como Executar o Projeto
1. Clone o repositório e configure o ambiente de desenvolvimento do `pico-sdk`.
2. Compile e carregue o código na Raspberry Pi Pico W.
3. Conecte os periféricos (matriz de LEDs, display OLED, botões).
4. Inicie o sistema e siga as instruções exibidas no display OLED.

## Possíveis Melhorias Futuras
- Implementar feedback sonoro para ações como pressionar botões ou validar a senha.
- Implementar litmite de respostas incorretas.

## Autor
Desenvolvido por [Rafhael Gaspar da silva](https://github.com/Rafhael0069).

## Licença
Este projeto foi desenvolvido para fins educacionais e pessoais. Sinta-se à vontade para explorar, modificar e utilizar como base para seus próprios projetos!