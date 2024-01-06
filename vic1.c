#include <avr/io.h>
#include <util/delay.h>

void strobe(uint8_t strobe_length) {
  // rising edge on PA7

  // set to zero, just to be sure
  PORTA &= ~(1 << PA7);

  //_delay_ms(10);
  // _delay_ms(1);
  _delay_us(100);

  // now make the rising edge
  PORTA |= (1 << PA7);

  switch(strobe_length) {
  case 0:
     _delay_us(200);
     break;
  case 1:
    _delay_ms(10);
    break;
  case 2:
  default:
    for (uint8_t i = 0; i < 10; ++i) {
      _delay_ms(100);
    }
    break;
  }

  // and we are done
  PORTA &= ~(1 << PA7);

  //_delay_us(100);
}

void write_char(uint8_t to_write, uint8_t strobe_length) {
  
  // mask highest bit to not accidentially
  // mess up strobe pin
  to_write &= 0x7F;

  PORTA = to_write;
  strobe(strobe_length);
  PORTA = 0x00;
}

void clear_screen() {
  write_char(0x0C, 2);
}

void cursor_home() {
  write_char(0x1C, 2);
}

void line_feed() {
  write_char(0x0A, 0);
}

void scroll() {
  write_char(0x1B, 1);
}

void carriage_return() {
  write_char(0x0D, 1);
}

void cursor_up() {
  write_char(0x0B, 0);
}

void cursor_down() {
  line_feed();
}

void cursor_right() {
  write_char(0x09, 0);
}

void cursor_left() {
  write_char(0x08, 0);
}

void write_string(const char* string_to_write) {
  while (*string_to_write) {
    char to_write = *string_to_write;

    if (to_write == 0x0D) {
      carriage_return();
    } else if (to_write == 0x0A) {
      line_feed();
    } else {
      write_char(to_write, 0);
    }

    string_to_write++;
  }
}



void tannenbaum() {
  write_string("           0                \r\n");
  write_string("           #                \r\n");
  write_string("          ###               \r\n");
  write_string("         #####              \r\n");
  write_string("          ###               \r\n");
  write_string("        #######             \r\n");
  write_string("       #########            \r\n");
  write_string("         #####              \r\n");
  write_string("      ###########           \r\n");
  write_string("     #############          \r\n");
  write_string("          ###    &          \r\n");
  write_string("          ###   ###         \r\n");
  write_string("          ###   ###         \r\n");
  write_string("                            \r\n");
  write_string(" Froehliche Weihnachten     \r\n");
  write_string(" von Klara und Jonathan!        ");
}

void moveto(uint8_t x, uint8_t y) {
  cursor_home();
  for (/* no-op */; x > 0; x--) {
    cursor_right();
  }
  for (/* no-op */; y > 0; y--) {
    cursor_down();
  }
}

void draw_frame() {
  cursor_home();
  for (uint8_t row = 0; row < 16; ++row) {
    for (uint8_t col = 0; col < 64; ++col) {
      uint8_t border_row = (row == 0 || row == 15);
      uint8_t border_col = (col == 0 || col == 63);

      if (border_row && border_col) {
        // corners
        write_char('+', 0);
      } else if (border_row) {
        write_char('-', 0);
      } else if (border_col) {
        write_char('!', 0);
      } else {
        cursor_right();
      }
      
      if (col == 63) {
        carriage_return();
      }
    }
  }
}


int main(int argc, char** argv) {

  DDRA = 0xff;
  PORTA = 0x00;

  clear_screen();
  //cursor_home();

  draw_frame();

//  moveto(0, 0);
//  tannenbaum();

  moveto(10, 10);
  write_string("test");

  moveto(20, 3);
  write_string("noch ein test");

/*
  moveto(0, 0);
  write_char('+', 0);

  moveto(63, 0);
  write_char('+', 0);

  moveto(63, 15);
  write_char('+', 0);

  moveto(0, 15);
  write_char('+', 0);
*/

  //uint8_t var = 0;
  while(1) {

/*
    write_string("Jonathan sagt: Hallo Klara!\r\n");
    _delay_ms(1000);
    write_string("   Klara sagt: Hallo Jonathan!\r\n");
    _delay_ms(1000);

    write_char('H', 0);
    write_char('A', 0);
    write_char('L', 0);
    write_char('L', 0);
    write_char('O', 0);
    write_char(' ', 0);
    write_char('K', 0);
    write_char('L', 0);
    write_char('A', 0);
    write_char('R', 0);
    write_char('A', 0);

    // also deleted rest of line
    // -> must be called before line feed
    //    in order to erase remainder
    //    of current line!
//    carriage_return();
//    line_feed();

    write_char(32 + var, 0);

    var = (var + 1) % 64;

    if (var == 0) {
      carriage_return();
      //line_feed();

      _delay_ms(1000);
    }
*/

  }



  return 0;
}
