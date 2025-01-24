# Leitor de Senha com Raspberry Pi Pico W

Este é um projeto pessoal desenvolvido como parte do curso da EmbarcaTech, utilizando a plataforma BitDogLab, baseada no microcontrolador Raspberry Pi Pico W. O objetivo do projeto é criar um sistema de leitura de senha interativo que combina uma matriz de LEDs RGB 5x5, um display OLED e botões de controle.

## Funcionalidades Planejadas

### 1. **Exibição de Números na Matriz de LEDs**
- Assim que o sistema é ligado, o número **0** é exibido na matriz de LEDs.
- Pressionar o **botão A** incrementa o número exibido, indo de **0 a 9** e reiniciando para **0** após o 9.

### 2. **Salvar Números na Lista de Senhas**
- Pressionar o **botão B** salva o número atualmente exibido na matriz de LEDs em uma lista.
- A lista de números salvos é exibida no display OLED.
- Após salvar, a matriz de LEDs reinicia para exibir o número **0**.

### 3. **Validação da Senha**
- Quando a lista de números salvos atinge 4 números, ela é comparada com uma lista de senha pré-programada.
  - Se as listas coincidem:
    - Um símbolo de **✓ (check)** é exibido na matriz de LEDs.
    - Uma mensagem de **"Boas-vindas"** é exibida no display OLED.
  - Se as listas não coincidem:
    - Um símbolo de **X** é exibido na matriz de LEDs.
    - Uma mensagem correspondente é exibida no display OLED.

## Componentes Utilizados
- **Microcontrolador:** Raspberry Pi Pico W
- **Plataforma:** BitDogLab
- **Sensores e Atuadores:**
  - Matriz de LEDs RGB 5x5
  - Display OLED
  - Botões (A e B)

## Requisitos
- Conhecimento em linguagem C para sistemas embarcados.
- Configuração da plataforma BitDogLab com os componentes mencionados.

## Estado Atual do Projeto
O projeto encontra-se em fase inicial de desenvolvimento. As funcionalidades descritas ainda estão sendo implementadas.

## Futuras Implementações
- Lógica para incrementar e exibir números na matriz de LEDs.
- Lógica para salvar e exibir a lista de números no display OLED.
- Validação da senha salva com a lista pré-programada.
- Exibição de mensagens de feedback no display OLED e na matriz de LEDs.

---

## Autor
Desenvolvido por [Rafhael Gaspar da silva](https://github.com/Rafhael0069).

## Licença
Este projeto foi desenvolvido para fins educacionais e pessoais. Sinta-se à vontade para explorar, modificar e utilizar como base para seus próprios projetos!