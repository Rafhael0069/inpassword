#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "matrix_control.h"
#include "matrices.h"
#include "oled_display.h"

#define BUTTON_A 5     // Definição do pino para o botão A
#define BUTTON_B 6     // Definição do pino para o botão B

#define DEBOUNCE_TIME_MS 200          // Tempo para evitar bouncing nos botões

const int matrix_brightness = 128;         // Brilho médio para LEDs da matriz
volatile uint32_t last_button_press_time = 0; // Armazena o último tempo de acionamento do botão

// Inicializa os botões configurando como entrada com pull-up
void init_buttons() {
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
}

// Função chamada nas interrupções dos botões
void button_callback(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    
    // Ignora eventos próximos (bouncing) com base no tempo configurado
    if (current_time - last_button_press_time < DEBOUNCE_TIME_MS) {
        return;
    }
    last_button_press_time = current_time;

    if (gpio_get(BUTTON_A) == 0) {
        const char *message[] = { "Botao A","Pressionado" };
        oled_display_message(message, 2); // Mostra mensagem no display OLED
    } else {
        const char *message[] = { "Botao B","Pressionado" };
        oled_display_message(message, 2); // Mostra mensagem no display OLED
    }
}

int main() {
    stdio_init_all(); // Inicializa a entrada e saída padrão

    // Configurações iniciais
    npInit(LED_PIN);  // Inicializa a matriz de LEDs
    oled_init();      // Inicializa o display OLED
    init_buttons();   // Configura os botões

    // Configura interrupções nos botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (1) {
        // Atualiza matriz de LEDs com a direção correta
        if (gpio_get(BUTTON_A) == 0 || gpio_get(BUTTON_B) == 0) {
            updateMatrix(x_pattern, 0, 0, 0); // Apaga matriz de LEDs como feedback
        } else {
            updateMatrix(x_pattern, 0, matrix_brightness, 0);
        }
        sleep_ms(10);
    }
}
