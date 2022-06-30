#if !defined(__LIB_USART_HPP__)
#define __LIB_USART_HPP__

#ifdef __cplusplus
extern "C" {
#endif

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;

#ifdef __cplusplus
}
#endif

namespace hal {

class UART {
public:
    UART(UART_HandleTypeDef* huart);

    void transmit(uint8_t byte, uint32_t timeout = 100);
    void transmit(uint8_t* data, size_t size, uint32_t timeout = 100);

    void receive_dma(uint8_t* data, size_t size);
    void receive_it(uint8_t* data, size_t size);
    void stop_dma();

    USART_TypeDef* instance() const;

private:
    UART_HandleTypeDef* huart;
};

} // namespace hal

#endif // __LIB_USART_HPP__
