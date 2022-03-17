#if !defined(__USART_HPP__)
#define __USART_HPP__

namespace hal {

class UART {
public:
    UART(UART_HandleTypeDef* huart);

    void transmit(uint8_t byte, uint32_t timeout = 100);
    void transmit(uint8_t* data, size_t size, uint32_t timeout = 100);

private:
    UART_HandleTypeDef* huart;
};

} // namespace hal

#endif // __USART_HPP__
