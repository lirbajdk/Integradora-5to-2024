#include <Arduino.h>
#include <onsa.h>

#define BOT1 ((PINC >> PC5) & 0x01)
#define BOT2 ((PINC >> PC4) & 0x01)
#define BOT3 ((PINC >> PC3) & 0x01)
#define BOT4 ((PINC >> PC2) & 0x01)
#define BOT5 ((PINC >> PC1) & 0x01)
#define BOT6 ((PINC >> PC0) & 0x01)

uint16_t numero = 0; // número
uint8_t decena, unidad, centena, miles;
uint16_t numero_falso;
int16_t dispa[10] = {
    //-abcdefg
    0b01110111, // 0
    0b01000001, // 1
    0b00111011, // 2
    0b01101011, // 3
    0b01001101, // 4
    0b01101110, // 5
    0b01111110, // 6
    0b01000011, // 7
    0b01111111, // 8
    0b01101111, // 9
   // 0b00000000, // nada
};
int16_t dispa2 = 0;

uint8_t descontando = 0; // este es el estado del desconteo (o sea la secuencia pedida ;D)
struct bot
{
    uint8_t flag_bot = 0, estarior = 0, press_bot = 0; // estarior = estado_anterior
    uint8_t incre_vel = 100;                           // esta es la velocidad a la que va a incrementar cuando se mantiene pulsado
};
bot bot1, bot2, bot3, bot4, bot5, bot6;

//-----INICIO-----DESCOMPONER-----INICIO-----//
/*void descompuesto(uint8_t miles1, uint8_t centena1, uint8_t decena1, uint8_t unidad1)
{
        numero--;
        // actualizar valores de miles, centenas, decenas y unidades
        miles1 = (numero / 1000) % 10;
        centena1 = (numero / 100) % 10;
        decena1 = (numero / 10) % 10;
        unidad1 = numero % 10;

} */
//-------FIN------DESCOMPONER------FIN-------//
///////////////////////////////////////////////
//------INICIO-----INTEGRADO-----INICIO------//
void integrado(uint8_t DS)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (DS & 1)
        {
            PORTD |= (1 << PD4); // poner en 1, el DS
        }
        else
        {
            PORTD &= ~(1 << PD4); // poner en 0, el DS
        }
        DS >>= 1;
        // generar el pulso del clk
        PORTD |= (1 << PD2); // establecer PD2 en 1 (SHT)
        _delay_us(1);
        PORTD &= ~(1 << PD2); // establecer PD2 en 0 (SHT)
        _delay_us(1);
    }
}
//-------FIN-------INTEGRADO-------FIN-------//
///////////////////////////////////////////////
//-----INICIO----FLAGS_BOTONES----INICIO-----//
void flags()
{
    uint8_t cnt_num = 100, fla_num = 20;
    //-------------------BOT_1-------------------//
    static uint8_t cnt_bot1 = 0;
    if (BOT1 == 0)
    {
        if (cnt_bot1 < cnt_num)
        {
            cnt_bot1++;
        }
    }
    else
    {
        cnt_bot1 = 0;
    }
    if (cnt_bot1 > fla_num)
    {
        bot1.flag_bot = 1;
    }
    else
    {
        bot1.flag_bot = 0;
    }

    //-------------------BOT_2-------------------//
    static uint8_t cnt_bot2 = 0;
    if (BOT2 == 0)
    {
        if (cnt_bot2 < cnt_num)
        {
            cnt_bot2++;
        }
    }
    else
    {
        cnt_bot2 = 0;
    }
    if (cnt_bot2 > fla_num)
    {
        bot2.flag_bot = 1;
    }
    else
    {
        bot2.flag_bot = 0;
    }
    //-------------------BOT_3-------------------//
    static uint8_t cnt_bot3 = 0;
    if (BOT3 == 0)
    {
        if (cnt_bot3 < cnt_num)
        {
            cnt_bot3++;
        }
    }
    else
    {
        cnt_bot3 = 0;
    }
    if (cnt_bot3 > fla_num)
    {
        bot3.flag_bot = 1;
    }
    else
    {
        bot3.flag_bot = 0;
    }
    //-------------------BOT_4-------------------//
    static uint8_t cnt_bot4 = 0;
    if (BOT4 == 0)
    {
        if (cnt_bot4 < cnt_num)
            cnt_bot4++;
    }
    else
    {
        cnt_bot4 = 0;
    }
    if (cnt_bot4 > fla_num)
    {
        bot4.flag_bot = 1;
    }
    else
    {
        bot4.flag_bot = 0;
    }
    //-------------------BOT_5-------------------//
    static uint8_t cnt_bot5 = 0;
    if (BOT5 == 0)
    {
        if (cnt_bot5 < cnt_num)
            cnt_bot5++;
    }
    else
    {
        cnt_bot5 = 0;
    }
    if (cnt_bot5 > fla_num)
    {
        bot5.flag_bot = 1;
    }
    else
    {
        bot5.flag_bot = 0;
    }
    //-------------------BOT_6-------------------//
    static uint8_t cnt_bot6 = 0;
    if (BOT6 == 0)
    {
        if (cnt_bot6 < cnt_num)
        {
            cnt_bot6++;
        }
    }
    else
    {
        cnt_bot6 = 0;
    }
    if (cnt_bot6 > fla_num)
    {
        bot6.flag_bot = 1;
    }
    else
    {
        bot6.flag_bot = 0;
    }
}
//------FIN------FLAGS_BOTONES------FIN------//
///////////////////////////////////////////////
//-----INICIO-----DESCONTADOR-----INICIO-----//
void descontador(uint8_t fin_cnteo = 0)
{
    // uint8_t estapera;
    if (descontando && numero != 0)
    {
        numero--;
        // actualizar valores de miles, centenas, decenas y unidades
        miles = (numero / 1000) % 10;
        centena = (numero / 100) % 10;
        decena = (numero / 10) % 10;
        unidad = numero % 10;
        PORTD |= (1 << PD7);
        _delay_us(10); // ajusta la velocidad del decremento

        //    final(estapera);

        // else{fin_cnteo = 0;}
    }
    else
    {
        PORTD &= ~(1 << PD7);
    }
    if (numero == 0)
    {
        fin_cnteo = 1;
        descontando = 0;
    }
    // if (fin_cnteo == 1)

    // uint16_t numero_falso = (miles * 1000) + (centena * 100) + (decena * 10) + unidad;
}
//-------FIN------DESCONTADOR------FIN-------//
///////////////////////////////////////////////
//-----INICIO-----LEER_BOTONES----INICIO-----//
void leer_bot_1a4()
{
    flags();
    //---INICIO---ANTIRREBOTES---INICIO---//
    if (!(dispa2 == dispa[8])) // esta parte de acá es para cuando finalice el desconteo los botones no puedan hacer nd
    {
        //----------------BOT1----------------//
        if (bot1.flag_bot == 1 && bot1.estarior == 0)
        {
            if (miles++ > 8)
                miles = 0; // descontando = 0;
        }
        bot1.estarior = bot1.flag_bot;
        /*//---POR SI SE MANTIENE EL BOT1---//
        if (bot1.flag_bot == 1)
        {
            if (bot1.press_bot > bot1.incre_vel)
            {
                miles++;
                if (miles > 9)
                    miles = 0;
                bot1.press_bot = 0;
            }
            else
            {
                bot1.press_bot++;
            }
        }
        else
        {
            bot1.press_bot = 0;
        }
        */
        //----------------BOT2----------------//
        if (bot2.flag_bot == 1 && bot2.estarior == 0)
        {
            if (centena++ > 8)
                centena = 0; // descontando = 0;
        }
        bot2.estarior = bot2.flag_bot;
        /*/---POR SI SE MANTIENE EL BOT2---//
        if (bot2.flag_bot == 1)
        {
            if (bot2.press_bot > bot2.incre_vel)
            {
                centena++;
                if (centena > 9)
                    centena = 0;
                bot2.press_bot = 0;
            }
            else
            {
                bot2.press_bot++;
            }
        }
        else
        {
            bot2.press_bot = 0;
        }*/
        //----------------BOT3----------------//
        if (bot3.flag_bot == 1 && bot3.estarior == 0)
        {
            if (decena++ > 8)
                decena = 0; // descontando = 0;
        }
        bot3.estarior = bot3.flag_bot;
        /*/---POR SI SE MANTIENE EL BOT3---//
        if (bot3.flag_bot == 1)
        {
            if (bot3.press_bot > bot3.incre_vel)
            {
                decena++;
                if (decena > 9)
                    decena = 0;
                bot3.press_bot = 0;
            }
            else
            {
                bot3.press_bot++;
            }
        }
        else
        {
            bot3.press_bot = 0;
        }*/
        //----------------BOT4----------------//
        if (bot4.flag_bot == 1 && bot4.estarior == 0)
        {
            if (unidad++ > 8)
                unidad = 0; // descontando = 0;
        }
        bot4.estarior = bot4.flag_bot;
        /*/---POR SI SE MANTIENE EL BOT4---//
        if (bot4.flag_bot == 1)
        {
            if (bot4.press_bot > bot4.incre_vel)
            {
                unidad++;
                if (unidad > 9)
                    unidad = 0;
                bot4.press_bot = 0;
            }
            else
            {
                bot4.press_bot++;
            }
        }
        else
        {
            bot4.press_bot = 0;
        }*/
    }
}
///////////////////////////////////////////////
void leer_bot_5y6(uint8_t detect_bot5 = 0)
{

    flags();
    static uint8_t num_frenao = 0;
    //----------------BOT5----------------//
    if (!(dispa2 == dispa[8])) // esta parte de acá es para cuando finalice el desconteo los botones no puedan hacer nd
    {
        if (bot5.flag_bot == 1 && bot5.estarior == 0)
        {
            detect_bot5++;
            if (detect_bot5 == 1) // CON ESTE IF pongo al numero pausado para proximamente renaudarlo desde allí, tambien guardo el valor seteado
            {
                num_frenao = numero;
                numero_falso = (miles * 1000) + (centena * 100) + (decena * 10) + unidad;
            }
            descontando = !descontando;
            _delay_ms(66);
            numero = numero_falso; // establecer el contador en seteado
        }
        bot5.estarior = bot5.flag_bot;
        if (detect_bot5 == 2) // CON ESTE IF veo el numero en el que se pausó el desconteop, así renaudarlo desde allí
        {
            numero = num_frenao; // en el numero en el que se pausó el desconteop, así renaudarlo desde allí
            /* con esto detecto si el bot 5 se pulsó durante el descuento lo cual lo frena y con este if lo
            devuelve al valor anteriormente seteado, (si se quisiera que el bot 5 al ser presionado por 2da
            vez y que no vuelva al valor seteado, y directamente vuelva a empezar a contar desde el numero interrumpido,
            entonces comente "detect_bot5" y sus if's)Actualizar los valores de miles, centenas, decenas y unidades*/
            miles = (numero / 1000) % 10;
            centena = (numero / 100) % 10;
            decena = (numero / 10) % 10;
            unidad = numero % 10;
            detect_bot5 = 0;
        }
    }
    //----------------BOT6----------------//
    if (bot6.flag_bot == 1 && bot6.estarior == 0)
    {
        miles = 0;
        centena = 0;
        decena = 0;
        unidad = 0;
        dispa2 = 0;
        descontando = 0;
        numero = 0;
        detect_bot5 = 0;
        // ya con este if simplemnte es para actualizar la flag
    }
    bot6.estarior = bot6.flag_bot;
}
//-------FIN------LEER_BOTONES------FIN------//
///////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
////////    ZONA NUMERICA    ////////////////////////////////////////////////////
void show(uint8_t tipo) // show es mostrar en inglés (creo)
{
    integrado(dispa2); // le mando 0 a los otros
    integrado(dispa2);
    integrado(dispa2);
    integrado(dispa[tipo]);
    integrado(dispa2);
}
////////    ZONA NUMERICA    ////////////////////////////////////////////////////
void showow() // el verdadero que muestra en los display
{
    // miles = (numero / 1000) % 10;
    // centena = (numero / 100) % 10;
    // decena = (numero / 10) % 10;
    // unidad = numero % 10;

    static uint16_t trans = 0; // trans de transistor    // apaga los trans
    PORTB &= ~(1 << PB3);
    PORTB &= ~(1 << PB2);
    PORTB &= ~(1 << PB1);
    PORTB &= ~(1 << PB0);
    // enviar datos a todos los 74HC595, pero solo al numero 4
    switch (trans)
    {
    case 0:
        show(miles);
        PORTB |= (1 << PB0); // prender el trans del display de los miles
        break;
    case 1:
        show(centena);
        PORTB |= (1 << PB1); // prender el trans del display de las centenas
        break;
    case 2:
        show(decena);
        PORTB |= (1 << PB2); // prender el trans del display de las decenas
        break;
    case 3:
        show(unidad);
        PORTB |= (1 << PB3); // prender el trans del display de las unidades
        break;
    }
    // generar el pulso de latch para actualizar las salidas
    PORTD |= (1 << PD3); // establecer PD3 en 1 (STC)
    _delay_us(2);
    PORTD &= ~(1 << PD3); // establecer PD3 en 0 (STC)
    _delay_us(2);
    trans++;
    if (trans > 3)
        trans = 0;
}

void show8888(uint8_t activo) // el verdadero que muestra en los display
{
    if (activo)
    {
        integrado(dispa[8]); // le mando 0 a los otros
        integrado(dispa[8]);
        integrado(dispa[8]);
        integrado(dispa[8]);
        integrado(dispa[8]);
        PORTB |= (1 << PB0); // prender el trans del display de los miles
        PORTB |= (1 << PB1); // prender el trans del display de las centenas
        PORTB |= (1 << PB2); // prender el trans del display de las decenas
        PORTB |= (1 << PB3); // prender el trans del display de las unidades
    }
    else
    {
        PORTB &= ~(1 << PB3);
        PORTB &= ~(1 << PB2);
        PORTB &= ~(1 << PB1);
        PORTB &= ~(1 << PB0);
    }

    // generar el pulso de latch para actualizar las salidas
    PORTD |= (1 << PD3); // establecer PD3 en 1 (STC)
    _delay_us(2);
    PORTD &= ~(1 << PD3); // establecer PD3 en 0 (STC)
    _delay_us(2);
}

static uint8_t fin_cnteo = 0;

int main(void)
{
    // Configurar Timer0
    setup_timer0();
    config_io();
    // habilitar interrupciones globales
    sei();
    // uint16_t numerico;
    miles = (numero / 1000) % 10;
    centena = (numero / 100) % 10;
    decena = (numero / 10) % 10;
    unidad = numero % 10;

    while (1)
    {
        if (descontando == 1)
        {
            descontador(fin_cnteo);
            if (miles + centena + decena + unidad == 0)
                fin_cnteo = 1;
        }
        else
        {
            PORTD &= ~(1 << PD7);
        }
        // if (bot6.flag_bot == 1 && bot6.estarior == 0)fin_cnteo = 0;

        if (fin_cnteo == 0)
            showow();

        if (miles + centena + decena + unidad != 0) // esto mas que nada está para que blos botones 5 y 6 no hagan nada al principio dewl programa ya que eso trabaria a los otras 4 teclas
            leer_bot_5y6();
        leer_bot_1a4(); // leer botones para actualizar los dígitos

        _delay_ms(2);
    }
}
/////////////////////////////////////////////////////////////////////////////////
ISR(TIMER0_COMPA_vect)
{
    static uint16_t cnt = 0;
    static uint8_t parpadeo = 0;
    if (bot6.flag_bot == 1 && bot6.estarior == 0)
    {
        fin_cnteo = 0;
        PORTD &= ~(1 << PD6);
    }
    if (cnt++ > 200)
    {
        cnt = 0;

        if (fin_cnteo == 1)
        {
            parpadeo = !parpadeo;
            show8888(parpadeo);
            PORTD |= (1 << PD6);
            PORTD &= ~(1 << PD7);
        }
    }
}