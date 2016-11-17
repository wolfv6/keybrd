#ifndef INSTANTIATIONS_SCANCODENOTSHIFTED_H
#define INSTANTIATIONS_SCANCODENOTSHIFTED_H

/* This file instandiates Code_ScNS objects for multiple-layer keybrd sketches.
The scancode is always sent in the unshifted state regardless of shift key position.
Letters will still print as capital if CapsLck is on.

If your uC is low on memory, copy needed lines rather than including the entire file.
With the Arduino IDE, objects consume memory if they are used or not.

The scancode macros are defined in the top part of
Arduino\hardware\teensy\cores\teensy\keylayouts.h which is intended for use in "normal" programs.
This has been tested on teensy2.0.
*/
#include <Code_ScNS.h>
#include <Code_ScNS_00.h>

// ********** SCANCODES NOT SHIFTED *********
Code_ScNS_00 ns_00;                             //double zero

Code_ScNS ns_1(KEY_1);                          //could get similar effect with s_pad1
Code_ScNS ns_2(KEY_2);
Code_ScNS ns_3(KEY_3);
Code_ScNS ns_4(KEY_4);
Code_ScNS ns_5(KEY_5);
Code_ScNS ns_6(KEY_6);
Code_ScNS ns_7(KEY_7);
Code_ScNS ns_8(KEY_8);
Code_ScNS ns_9(KEY_9);
Code_ScNS ns_0(KEY_0);

Code_ScNS ns_minus(KEY_MINUS);                  //could get similar effect with s_padMinus
Code_ScNS ns_equal(KEY_EQUAL);
Code_ScNS ns_leftBracket(KEY_LEFT_BRACE);       //[ ("brace" means curly bracket {})
Code_ScNS ns_rightBracket(KEY_RIGHT_BRACE);     //]
Code_ScNS ns_backslash(KEY_BACKSLASH);
Code_ScNS ns_semicolon(KEY_SEMICOLON);
Code_ScNS ns_quote(KEY_QUOTE);
Code_ScNS ns_tilde(KEY_TILDE);
Code_ScNS ns_comma(KEY_COMMA);
Code_ScNS ns_period(KEY_PERIOD);
Code_ScNS ns_slash(KEY_SLASH);
