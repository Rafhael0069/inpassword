#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "matrix_control.h"
#include "matrices.h"
#include "oled_display.h"

#define BUTTON_A 5 // Definição do pino para o botão A
#define BUTTON_B 6 // Definição do pino para o botão B

#define DEBOUNCE_TIME_MS 200 // Tempo para evitar bouncing nos botões
#define MAX_NUMBERS 4       // Número máximo de números armazenados na lista

const int matrix_brightness = 128;            // Brilho médio para LEDs da matriz
volatile uint32_t last_button_press_time = 0; // Armazena o último tempo de acionamento do botão
volatile int current_number = 0;              // Número atual exibido na matriz de LEDs
volatile bool clear_matrix = false;           // Indica se a matriz deve ser apagada momentaneamente
int saved_numbers[MAX_NUMBERS];               // Lista de números salvos
int saved_count = 0;                          // Quantidade de números salvos na lista

const int predefined_password[MAX_NUMBERS] = {0, 0, 0, 0}; // Senha predefinida

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
    case 0: updateMatrix(number_0, 0, 0, matrix_brightness); break;
    case 1: updateMatrix(number_1, 0, 0, matrix_brightness); break;
    case 2: updateMatrix(number_2, 0, 0, matrix_brightness); break;
    case 3: updateMatrix(number_3, 0, 0, matrix_brightness); break;
    case 4: updateMatrix(number_4, 0, 0, matrix_brightness); break;
    case 5: updateMatrix(number_5, 0, 0, matrix_brightness); break;
    case 6: updateMatrix(number_6, 0, 0, matrix_brightness); break;
    case 7: updateMatrix(number_7, 0, 0, matrix_brightness); break;
    case 8: updateMatrix(number_8, 0, 0, matrix_brightness); break;
    case 9: updateMatrix(number_9, 0, 0, matrix_brightness); break;
    default: updateMatrix(number_0, 0, 0, matrix_brightness); break;
    }
}

// Reinicia o estado do programa
void reset_program_state() {
    saved_count = 0;         // Reinicia o contador de números salvos
    current_number = 0;      // Reinicia o ciclo de números
    clear_matrix = true;     // Apaga a matriz temporariamente
    memset(saved_numbers, 0, sizeof(saved_numbers)); // Limpa a lista de números salvos

    // Atualiza o display OLED para o estado inicial
    const char *message[] = {"Insira", "A senha"};
    oled_display_message(message, 2);

     // Limpa a matriz de LEDs
    updateMatrix(x_pattern, 0, 0, 0);
}


// Mostra a lista de números salvos no display OLED
void display_saved_numbers() {
    char display_buffer[64];
    memset(display_buffer, 0, sizeof(display_buffer));

    // Constrói a string com os números salvos
    if (saved_count == 0) {
        snprintf(display_buffer, sizeof(display_buffer), "Lista vazia");
    } else {
        snprintf(display_buffer, sizeof(display_buffer), "");
        for (int i = 0; i < saved_count; i++) {
            char num_str[4];
            snprintf(num_str, sizeof(num_str), " %d", saved_numbers[i]);
            strncat(display_buffer, num_str, sizeof(display_buffer) - strlen(display_buffer) - 1);
        }
    }

    const char *message[] = {"Salvos:", "  ", display_buffer};
    oled_display_message(message, 3); // Exibe a lista no display OLED
}

// Verifica se a lista de números salvos coincide com a senha predefinida
bool is_password_correct() {
    for (int i = 0; i < MAX_NUMBERS; i++) {
        if (saved_numbers[i] != predefined_password[i]) {
            return false;
        }
    }
    return true;
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
    } else if (gpio == BUTTON_B && gpio_get(BUTTON_B) == 0) {
        // Salva o número atual na lista
        if (saved_count < MAX_NUMBERS) {
            saved_numbers[saved_count++] = current_number;
        }

        // Exibe a lista de números salvos no OLED
        display_saved_numbers();

        if (saved_count == MAX_NUMBERS) {
            if (is_password_correct()) {
                const char *message[] = {"Senha", "Correta"};
                oled_display_message(message, 2);
                updateMatrix(checked_pattern, 0, matrix_brightness, 0); // Exibe um "V" na matriz
            } else {            
                const char *message[] = {"Senha", "Incorreta"};
                oled_display_message(message, 2);
                updateMatrix(x_pattern, matrix_brightness, 0, 0); // Exibe um "X" na matriz
            }
            sleep_ms(3000);          // Espera 3 segundos antes de reiniciar
            reset_program_state();   // Reinicia o estado do program
        }
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

    reset_program_state(); // Inicializa o estado inicial

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