#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "matrix_control.h"
#include "matrices.h"
#include "oled_display.h"

#define BUTTON_A 5 // Definição do pino para o botão A
#define BUTTON_B 6 // Definição do pino para o botão B

#define DEBOUNCE_TIME_MS 200 // Tempo para evitar bouncing nos botões

const int matrix_brightness = 128;            // Brilho médio para LEDs da matriz
volatile uint32_t last_button_press_time = 0; // Armazena o último tempo de acionamento do botão
volatile int current_number = 0;              // Número atual exibido na matriz de LEDs
volatile bool clear_matrix = false;           // Indica se a matriz deve ser apagada momentaneamente

// Inicializa os botões configurando como entrada com pull-up
void init_buttons() {
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
}

// Atualiza a matriz de LEDs para exibir o número atual
void display_number_on_matrix(int number) {
    switch (number) {
    case 0:
        updateMatrix(number_0, 0, 0, matrix_brightness);
        break;
    case 1:
        updateMatrix(number_1, 0, 0, matrix_brightness);
        break;
    case 2:
        updateMatrix(number_2, 0, 0, matrix_brightness);
        break;
    case 3:
        updateMatrix(number_3, 0, 0, matrix_brightness);
        break;
    case 4:
        updateMatrix(number_4, 0, 0, matrix_brightness);
        break;
    case 5:
        updateMatrix(number_5, 0, 0, matrix_brightness);
        break;
    case 6:
        updateMatrix(number_6, 0, 0, matrix_brightness);
        break;
    case 7:
        updateMatrix(number_7, 0, 0, matrix_brightness);
        break;
    case 8:
        updateMatrix(number_8, 0, 0, matrix_brightness);
        break;
    case 9:
        updateMatrix(number_9, 0, 0, matrix_brightness);
        break;
    default:
        updateMatrix(number_0, 0, 0, matrix_brightness);
        break;
    }
}

// Função chamada nas interrupções dos botões
void button_callback(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // Ignora eventos próximos (bouncing) com base no tempo configurado
    if (current_time - last_button_press_time < DEBOUNCE_TIME_MS) {
        return;
    }
    last_button_press_time = current_time;

    clear_matrix = true; // Indica que a matriz deve ser apagada momentaneamente

    if (gpio == BUTTON_A && gpio_get(BUTTON_A) == 0) {
        current_number = (current_number + 1) % 10; // Incrementa o número e reinicia após 9
        const char *message[] = {"Botao A", "Pressionado"};
        oled_display_message(message, 2); // Mostra mensagem no display OLED
    } else if (gpio == BUTTON_B && gpio_get(BUTTON_B) == 0) {
        const char *message[] = {"Botao B", "Pressionado"};
        oled_display_message(message, 2); // Mostra mensagem no display OLED
    }
}

int main() {
    stdio_init_all(); // Inicializa a entrada e saída padrão

    // Configurações iniciais
    npInit(LED_PIN); // Inicializa a matriz de LEDs
    oled_init();     // Inicializa o display OLED
    init_buttons();  // Configura os botões

    // Configura interrupções nos botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_callback);


    while (1) {
        if (clear_matrix) {
            updateMatrix(x_pattern, 0, 0, 0); // Apaga matriz de LEDs
            sleep_ms(100);                   // Pequeno atraso para o feedback visual
            clear_matrix = false;            // Restaura o estado para exibir o número atual
        }
        display_number_on_matrix(current_number); // Exibe o número atual
        sleep_ms(10);
    }
}