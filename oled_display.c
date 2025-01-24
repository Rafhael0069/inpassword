#include <string.h>
#include "oled_display.h"

// Buffer e área de renderização
static uint8_t ssd[ssd1306_buffer_length];
static struct render_area frame_area;

void oled_init() {
    // Inicialização do I2C e do display SSD1306
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(14, GPIO_FUNC_I2C);
    gpio_set_function(15, GPIO_FUNC_I2C);
    gpio_pull_up(14);
    gpio_pull_up(15);

    ssd1306_init();

    // Configura a área de renderização
    frame_area.start_column = 0;
    frame_area.end_column = ssd1306_width - 1;
    frame_area.start_page = 0;
    frame_area.end_page = ssd1306_n_pages - 1;
    calculate_render_area_buffer_length(&frame_area);

    oled_clear();
}

void oled_clear() {
    // Limpa o conteúdo do display
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);
}

void oled_display_message(const char *messages[], size_t line_count) {
    oled_clear();

    // Calcula o deslocamento vertical para centralizar as mensagens
    int total_height = line_count * 8;  // Cada linha tem 8 pixels de altura
    int start_y = (64 - total_height) / 2;

    for (size_t i = 0; i < line_count; i++) {
        int message_length = strlen(messages[i]);
        int start_x = (128 - (message_length * 6)) / 2;  // Cada caractere tem 6 pixels de largura

        // Exibe cada linha no display
        ssd1306_draw_string(ssd, start_x, start_y + (i * 8), messages[i]);
    }

    render_on_display(ssd, &frame_area);
}
