/* Include this file in multiple-layer keybrd sketches.
This file instandiates Code objects.

The scancode macros are defined in the top part of
Arduino\hardware\teensy\cores\teensy\keylayouts.h which is intended for use in "normal" programs.
This has been tested on teensy2.0.
*/
#include <Code_Null.h>
#include <Code_Sc.h>
#include <Code_ScS.h>
#include <Code_Shift.h>

// ********** SCANCODES *********
Code_Shift s_shift(MODIFIERKEY_LEFT_SHIFT);
Code_Shift s_shift_L(MODIFIERKEY_LEFT_SHIFT);
Code_Shift s_shift_R(MODIFIERKEY_RIGHT_SHIFT);

Code_Sc s_ctrl(MODIFIERKEY_CTRL);
Code_Sc s_alt(MODIFIERKEY_ALT);
Code_Sc s_gui(MODIFIERKEY_GUI);
Code_Sc s_leftCtrl(MODIFIERKEY_LEFT_CTRL);
Code_Sc s_leftAlt(MODIFIERKEY_LEFT_ALT);
Code_Sc s_leftGUI(MODIFIERKEY_LEFT_GUI);
Code_Sc s_rightCtrl(MODIFIERKEY_RIGHT_CTRL);
Code_Sc s_rightAlt(MODIFIERKEY_RIGHT_ALT);
Code_Sc s_rightGUI(MODIFIERKEY_RIGHT_GUI);

Code_Sc s_MVolumeInc(KEY_MEDIA_VOLUME_INC);
Code_Sc s_MVolumeDec(KEY_MEDIA_VOLUME_DEC);
Code_Sc s_MMute(KEY_MEDIA_MUTE);
Code_Sc s_MPlayPause(KEY_MEDIA_PLAY_PAUSE);
Code_Sc s_MNextTrack(KEY_MEDIA_NEXT_TRACK);
Code_Sc s_MPrevTrack(KEY_MEDIA_PREV_TRACK);
Code_Sc s_MStop(KEY_MEDIA_STOP);
Code_Sc s_MEject(KEY_MEDIA_EJECT);

Code_Sc s_a(KEY_A);
Code_Sc s_b(KEY_B);
Code_Sc s_c(KEY_C);
Code_Sc s_d(KEY_D);
Code_Sc s_e(KEY_E);
Code_Sc s_f(KEY_F);
Code_Sc s_g(KEY_G);
Code_Sc s_h(KEY_H);
Code_Sc s_i(KEY_I);
Code_Sc s_j(KEY_J);
Code_Sc s_k(KEY_K);
Code_Sc s_l(KEY_L);
Code_Sc s_m(KEY_M);
Code_Sc s_n(KEY_N);
Code_Sc s_o(KEY_O);
Code_Sc s_p(KEY_P);
Code_Sc s_q(KEY_Q);
Code_Sc s_r(KEY_R);
Code_Sc s_s(KEY_S);
Code_Sc s_t(KEY_T);
Code_Sc s_u(KEY_U);
Code_Sc s_v(KEY_V);
Code_Sc s_w(KEY_W);
Code_Sc s_x(KEY_X);
Code_Sc s_y(KEY_Y);
Code_Sc s_z(KEY_Z);

Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);
Code_Sc s_4(KEY_4);
Code_Sc s_5(KEY_5);
Code_Sc s_6(KEY_6);
Code_Sc s_7(KEY_7);
Code_Sc s_8(KEY_8);
Code_Sc s_9(KEY_9);
Code_Sc s_0(KEY_0);

Code_Sc s_enter(KEY_ENTER);
Code_Sc s_esc(KEY_ESC);
Code_Sc s_backspace(KEY_BACKSPACE);
Code_Sc s_tab(KEY_TAB);
Code_Sc s_space(KEY_SPACE);
Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_leftBracket(KEY_LEFT_BRACE);           //[ ("brace" means curly bracket {})
Code_Sc s_rightBracket(KEY_RIGHT_BRACE);         //]
Code_Sc s_backslash(KEY_BACKSLASH);
Code_Sc s_semicolon(KEY_SEMICOLON);
Code_Sc s_quote(KEY_QUOTE);
Code_Sc s_graves(KEY_TILDE);                      //`
//Code_Sc s_graves(ASCII_60);                       //`
Code_Sc s_comma(KEY_COMMA);
Code_Sc s_period(KEY_PERIOD);
Code_Sc s_slash(KEY_SLASH);
Code_Sc s_capsLock(KEY_CAPS_LOCK);

Code_Sc s_F1(KEY_F1);
Code_Sc s_F2(KEY_F2);
Code_Sc s_F3(KEY_F3);
Code_Sc s_F4(KEY_F4);
Code_Sc s_F5(KEY_F5);
Code_Sc s_F6(KEY_F6);
Code_Sc s_F7(KEY_F7);
Code_Sc s_F8(KEY_F8);
Code_Sc s_F9(KEY_F9);
Code_Sc s_F10(KEY_F10);
Code_Sc s_F11(KEY_F11);
Code_Sc s_F12(KEY_F12);

Code_Sc s_printscreen(KEY_PRINTSCREEN);
Code_Sc s_scrollLock(KEY_SCROLL_LOCK);
Code_Sc s_pause(KEY_PAUSE);
Code_Sc s_insert(KEY_INSERT);
Code_Sc s_home(KEY_HOME);
Code_Sc s_pageUp(KEY_PAGE_UP);
Code_Sc s_delete(KEY_DELETE);
Code_Sc s_end(KEY_END);
Code_Sc s_pageDown(KEY_PAGE_DOWN);
Code_Sc s_right(KEY_RIGHT);                      //arrow
Code_Sc s_left(KEY_LEFT);
Code_Sc s_down(KEY_DOWN);
Code_Sc s_up(KEY_UP);
Code_Sc s_numLock(KEY_NUM_LOCK);

Code_Sc s_padSlash(KEYPAD_SLASH);
Code_Sc s_padAsterix(KEYPAD_ASTERIX);
Code_Sc s_padMinus(KEYPAD_MINUS);
Code_Sc s_padPlus(KEYPAD_PLUS);
Code_Sc s_padEnter(KEYPAD_ENTER);
Code_Sc s_pad1(KEYPAD_1);
Code_Sc s_pad2(KEYPAD_2);
Code_Sc s_pad3(KEYPAD_3);
Code_Sc s_pad4(KEYPAD_4);
Code_Sc s_pad5(KEYPAD_5);
Code_Sc s_pad6(KEYPAD_6);
Code_Sc s_pad7(KEYPAD_7);
Code_Sc s_pad8(KEYPAD_8);
Code_Sc s_pad9(KEYPAD_9);
Code_Sc s_pad0(KEYPAD_0);
Code_Sc s_padPeriod(KEYPAD_PERIOD);

Code_Sc s_menu(KEY_MENU);
Code_Sc s_F13(KEY_F13);
Code_Sc s_F14(KEY_F14);
Code_Sc s_F15(KEY_F15);
Code_Sc s_F16(KEY_F16);
Code_Sc s_F17(KEY_F17);
Code_Sc s_F18(KEY_F18);
Code_Sc s_F19(KEY_F19);
Code_Sc s_F20(KEY_F20);
Code_Sc s_F21(KEY_F21);
Code_Sc s_F22(KEY_F22);
Code_Sc s_F23(KEY_F23);
Code_Sc s_F24(KEY_F24);

// ********** SCANCODES SHIFTED *********
// shifted objects are named after ascii symbol names
Code_ScS s_exclamation(KEY_1);
Code_ScS s_at(KEY_2);
Code_ScS s_number(KEY_3);                        //#
Code_ScS s_dollar(KEY_4);
Code_ScS s_percent(KEY_5);
Code_ScS s_circumflex(KEY_6);                    //^
Code_ScS s_ampersand(KEY_7);
Code_ScS s_asterix(KEY_8);
Code_ScS s_leftParen(KEY_9);                     //parenthesis
Code_ScS s_rightParen(KEY_0);

Code_ScS s_underscore(KEY_MINUS);
Code_ScS s_plus(KEY_EQUAL);
Code_ScS s_leftBrace(KEY_LEFT_BRACE);            //{
Code_ScS s_rightBrace(KEY_RIGHT_BRACE);          //}
Code_ScS s_vertBar(KEY_BACKSLASH);               //|
Code_ScS s_colon(KEY_SEMICOLON);
Code_ScS s_doubleQuote(KEY_QUOTE);
Code_ScS s_tilde(KEY_TILDE);
Code_ScS s_lessThan(KEY_COMMA);
Code_ScS s_greaterThan(KEY_PERIOD);
Code_ScS s_question(KEY_SLASH);

// ********** MISC CODES *********
Code_Null code_null;                            //useful for blank keys
