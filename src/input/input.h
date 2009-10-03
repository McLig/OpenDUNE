/* $Id$ */

#ifndef INPUT_H
#define INPUT_H

/**
 * Several flags for input handling.
 */
typedef enum InputFlagsEnum {
	INPUT_FLAG_KEY_REPEAT   = 0x0001,              //!< Allow repeated input of the same key.
	INPUT_FLAG_UNKNOWN_0002 = 0x0002,              //!< ??
	INPUT_FLAG_UNKNOWN_0200 = 0x0200,              //!< ??
	INPUT_FLAG_KEY_RELEASE  = 0x0800,              //!< Record release of keys (not for buttons).
	INPUT_FLAG_NO_CLICK     = 0x1000,              //!< Don't record mouse button clicks.
} InputFlagsEnum;

/**
 * There are three different mouse modes.
 *  It looks like only the first (normal) mode is ever used.
 */
typedef enum InputMouseMode {
	INPUT_MOUSE_MODE_NORMAL = 0,                   //!< Normal mouse mode.
	INPUT_MOUSE_MODE_1      = 1,                   //!< ??
	INPUT_MOUSE_MODE_2      = 2,                   //!< ?? Only button clicks.
} InputMouseMode;

MSVC_PACKED_BEGIN;
/**
 * Local input variables at segment 29E8.
 */
typedef struct InputLocalData {
	/* 0000()    */ uint8   unknown_0000[0x002E];
	/* 002E(8)   */ uint8  bitmask[8];             //!< The value of (1 << N), with N from 0 to 7.
	/* 0036()    */ uint8   unknown_0036[0x0058];
	/* 008E(16)  */ uint8  translateMap[16];       //!< ?? Some kind of translation map.
	/* 009E(16)  */ uint8  translateTo[16];        //!< ?? To what a match in the above map translates.
	/* 00AE(1)   */ uint8   unknown_00AE[1];
	/* 00AF(256) */ uint16 history[128];           //!< History of input commands.
	/* 01AF(2)   */ uint16 historyHead;            //!< The current head inside the history array.
	/* 01B1(2)   */ uint16 historyTail;            //!< The current tail inside the history array.
	/* 01B3(2)   */ uint16 flags;                  //!< Mask for allowed input types. See InputFlagsEnum.
	/* 01B5()    */ uint16 variable_01B5;          //!< ??
	/* 01B7(2)   */ uint16 variable_01B7;          //!< ??
	/* 01B9()    */ uint8   unknown_01B9[0x0059];
	/* 0212(8)   */ uint8  keymap_special_mask[8]; //!< Per bit, mask which keys are special and should be done &= 0x1F.
	/* 021A()    */ uint8   unknown_021A[0x0018];
	/* 0232(16)  */ uint8  activeInputMap[16];     //!< A 96 bit array, where each active bit means that the Nth key is pressed.
	/* 0242()    */ uint8   unknown_0242[0x001E];
	/* 0260(11)  */ uint8  keymap_ignore[11];      //!< Keys to ignore when reading.
	/* 026B()    */ uint8   unknown_026B[0x0001];

	/* 026C(222) */ uint8      code_026C[222];
	/* 034A(62)  */ uint8  keymap_normal[62];      //!< Keymap to convert scancode to ASCII with capslock off and shift released.
	/* 0388(62)  */ uint8  keymap_shift[62];       //!< Keymap to convert scancode to ASCII with capslock off and shift pressed.
	/* 03C6(62)  */ uint8  keymap_capslock[62];    //!< Keymap to convert scancode to ASCII with capslock on and shift released.
	/* 0404(62)  */ uint8  keymap_caps_shift[62];  //!< Keymap to convert scancode to ASCII with capslock on and shift pressed.
	/* 0442(35)  */ uint8  keymap_numpad[35];      //!< Keymap to convert scancode to for numpad with numlock off.
	/* 0465(20)  */ uint8  keymap_numlock[20];     //!< Keymap to convert scancode to for numpad with numlock on.

	/* 0479(185) */ uint8      code_0479[187];
	/* 0534()    */ uint8   unknown_0534[0x010F];
	/* 0643(125) */ uint8      code_0643[125];
	/* 06C0()    */ uint8   unknown_06C0[0x007F];
	/* 073F(14)  */ uint8      code_073F[14];
	/* 074D()    */ uint8   unknown_074D[0x02CC];

	/* 0A19(123) */ uint8      code_0A19[123];
	/* 0A94(2)   */ uint16 variable_0A94;          //!< ??
	/* 0A96(2)   */ uint16 variable_0A96;          //!< ?? Set to the same as 353F:76A6.
	/* 0A98(2)   */ uint16 mouseX;                 //!< Current X position of the mouse.
	/* 0A9A(2)   */ uint16 mouseY;                 //!< Current Y position of the mouse.

	/* 0A9C()    */ uint8   unknown_0A9C[0x003A];
	/* 0AD6(16)  */ uint8      code_0AD6[16];
	/* 0AE6()    */ uint8   unknown_0AE6[0x015A];
	/* 0C40(263) */ uint8      code_0C40[263];
	/* 0D47()    */ uint8   unknown_0D47[0x024E];
	/* 0F95()    */ // Last known byte
} GCC_PACKED InputLocalData;
MSVC_PACKED_END;
assert_compile(sizeof(InputLocalData) == 0x0F95);

extern void System_Init_Input();
extern void Input_Mouse_Init();
extern void Input_Mouse_EventHandler();
extern void Input_Mouse_InsideRegion();
extern void Input_Mouse_CallbackClear();
extern void Input_Flags_ClearBits();
extern void Input_Flags_SetBits();
extern void Input_History_Clear();
extern void Input_Keyboard_HandleKeys(uint8 key, uint8 state);
extern void Input_Keyboard_HandleKeys2();
extern void Input_Keyboard_Translate();
extern void Input_Unknown_04FC();
extern void Input_Keyboard_NextKey();
extern void Input_HandleInputSafe();

#endif /* INTPUT_H */
