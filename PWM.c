#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Definições dos pinos
#define SERVO_PIN 22       // Pino do servomotor
#define LED_PIN_RED 13     // Pino do LED RGB (canal vermelho)
#define LED_PIN_GREEN 11   // Pino do LED RGB (canal verde)
#define LED_PIN_BLUE 12    // Pino do LED RGB (canal azul)

// Definições do PWM
#define PWM_WRAP 20000     // Período de 20ms (50Hz)
#define PWM_CLK_DIV 64     // Divisor de clock para o PWM

// Função para ajustar a posição do servomotor
void set_servo_position(uint slice_num, uint channel, uint pulse_width_us) {
    uint pulse_width = pulse_width_us * PWM_WRAP / 20000;
    pwm_set_chan_level(slice_num, channel, pulse_width);
}

// Função para ajustar a cor do LED RGB
void set_led_color(uint8_t red, uint8_t green, uint8_t blue) {
    pwm_set_gpio_level(LED_PIN_RED, red);
    pwm_set_gpio_level(LED_PIN_GREEN, green);
    pwm_set_gpio_level(LED_PIN_BLUE, blue);
}

int main() {
    // Inicialização do sistema
    stdio_init_all();

    // Configuração do PWM para o servomotor
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num_servo = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel_servo = pwm_gpio_to_channel(SERVO_PIN);

    pwm_config config_servo = pwm_get_default_config();
    pwm_config_set_wrap(&config_servo, PWM_WRAP);
    pwm_config_set_clkdiv(&config_servo, PWM_CLK_DIV);
    pwm_init(slice_num_servo, &config_servo, true);

    // Configuração do PWM para o LED RGB
    gpio_set_function(LED_PIN_RED, GPIO_FUNC_PWM);
    gpio_set_function(LED_PIN_GREEN, GPIO_FUNC_PWM);
    gpio_set_function(LED_PIN_BLUE, GPIO_FUNC_PWM);

    uint slice_num_red = pwm_gpio_to_slice_num(LED_PIN_RED);
    uint slice_num_green = pwm_gpio_to_slice_num(LED_PIN_GREEN);
    uint slice_num_blue = pwm_gpio_to_slice_num(LED_PIN_BLUE);

    pwm_config config_led = pwm_get_default_config();
    pwm_config_set_wrap(&config_led, 255); // 8-bit resolution for LED
    pwm_init(slice_num_red, &config_led, true);
    pwm_init(slice_num_green, &config_led, true);
    pwm_init(slice_num_blue, &config_led, true);

    // Posicionamento inicial do servomotor (0 graus)
    set_servo_position(slice_num_servo, channel_servo, 500);
    set_led_color(255, 0, 0); // LED vermelho
    sleep_ms(5000);

    // Posicionamento do servomotor em 90 graus
    set_servo_position(slice_num_servo, channel_servo, 1470);
    set_led_color(0, 255, 0); // LED verde
    sleep_ms(5000);

    // Posicionamento do servomotor em 180 graus
    set_servo_position(slice_num_servo, channel_servo, 2400);
    set_led_color(0, 0, 255); // LED azul
    sleep_ms(5000);

    // Movimentação periódica do servomotor entre 0 e 180 graus
    while (true) {
        // Movimento de 0° a 180°
        for (uint pulse_width = 500; pulse_width <= 2400; pulse_width += 5) {
            set_servo_position(slice_num_servo, channel_servo, pulse_width);
            set_led_color(255 - (pulse_width - 500) / 7, 0, (pulse_width - 500) / 7); // Transição de vermelho para azul
            sleep_ms(10);
        }

        // Movimento de 180° a 0°
        for (uint pulse_width = 2400; pulse_width >= 500; pulse_width -= 5) {
            set_servo_position(slice_num_servo, channel_servo, pulse_width);
            set_led_color(255 - (pulse_width - 500) / 7, 0, (pulse_width - 500) / 7); // Transição de azul para vermelho
            sleep_ms(10);
        }
    }

    return 0;
}