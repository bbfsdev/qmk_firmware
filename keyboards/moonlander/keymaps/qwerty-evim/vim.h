#include "config.h"
#include "print.h"
#include "keycode.h"
#include "quantum.h"
#include "quantum_keycodes.h"

#define NOR_MOD TO(NORMAL_MODE)
#define INS_MOD TO(INSERT_MODE)

#define PRESS(keycode) register_code(keycode)
#define RELEASE(keycode) unregister_code(keycode)

uint16_t VIM_QUEUE = KC_NO;

enum vim_custom_keycodes {
  PLACEHOLDER = SAFE_RANGE + 10000, // can always be here
  VIM_A,
  VIM_B,
  VIM_C,
  VIM_CI,
  VIM_D,
  VIM_DI,
  VIM_E,
  VIM_H,
  VIM_I,
  VIM_J,
  VIM_K,
  VIM_L,
  VIM_O,
  VIM_P,
  VIM_R,
  VIM_S,
  VIM_U,
  VIM_V,
  VIM_VI,
  VIM_W,
  VIM_X,
  VIM_Y,
  EPRM,
  VRSN,
};

void VIM_APPEND(void);
void VIM_APPEND_LINE(void);
void VIM_BACK(void);
void VIM_CHANGE_BACK(void);
void VIM_CHANGE_DOWN(void);
void VIM_CHANGE_END(void);
void VIM_CHANGE_INNER_WORD(void);
void VIM_CHANGE_LEFT(void);
void VIM_CHANGE_LINE(void);
void VIM_CHANGE_RIGHT(void);
void VIM_CHANGE_UP(void);
void VIM_CHANGE_WHOLE_LINE(void);
void VIM_CHANGE_WORD(void);
void VIM_CUT(void);
void VIM_DELETE_BACK(void);
void VIM_DELETE_DOWN(void);
void VIM_DELETE_END(void);
void VIM_DELETE_INNER_WORD(void);
void VIM_DELETE_LEFT(void);
void VIM_DELETE_LINE(void);
void VIM_DELETE_RIGHT(void);
void VIM_DELETE_UP(void);
void VIM_DELETE_WHOLE_LINE(void);
void VIM_DELETE_WORD(void);
void VIM_END(void);
void VIM_JOIN(void);
void VIM_OPEN(void);
void VIM_OPEN_ABOVE(void);
void VIM_PUT(void);
void VIM_REDO(void);
void VIM_SUBSTITUTE(void);
void VIM_UNDO(void);
void VIM_VISUAL_BACK(void);
void VIM_VISUAL_DOWN(void);
void VIM_VISUAL_END(void);
void VIM_VISUAL_INNER_WORD(void);
void VIM_VISUAL_LEFT(void);
void VIM_VISUAL_RIGHT(void);
void VIM_VISUAL_UP(void);
void VIM_VISUAL_WORD(void);
void VIM_WORD(void);
void VIM_YANK(void);

void TAP(uint16_t keycode) {
    PRESS(keycode);
    RELEASE(keycode);
}

void CMD(uint16_t keycode) {
  //PRESS(KC_LGUI);
  PRESS(KC_LCTRL);
    TAP(keycode);
  //RELEASE(KC_LGUI);
  RELEASE(KC_LCTRL);
}

void CTRL(uint16_t keycode) {
  PRESS(KC_LCTRL);
    TAP(keycode);
  RELEASE(KC_LCTRL);
}

void SHIFT(uint16_t keycode) {
  PRESS(KC_LSHIFT);
    TAP(keycode);
  RELEASE(KC_LSHIFT);
}

void ALT(uint16_t keycode) {
  PRESS(KC_LALT);
    TAP(keycode);
  RELEASE(KC_LALT);
}

/**
 * Sets the `VIM_QUEUE` variable to the incoming keycode.
 * Pass `KC_NO` to cancel the operation.
 * @param keycode
 */
void VIM_LEADER(uint16_t keycode) {
  VIM_QUEUE = keycode;
  switch(keycode) {
    case VIM_C: print("VIM_LEADER VIM_C\n"); break;
    case VIM_CI: print("VIM_LEADER VIM_CI\n"); break;
    case VIM_D: print("VIM_LEADER VIM_D\n"); break;
    case VIM_DI: print("VIM_LEADER VIM_DI\n"); break;
    case VIM_V: print("VIM_LEADER VIM_V\n"); break;
    case VIM_VI: print("VIM_LEADER VIM_VI\n"); break;
    case KC_NO: print("VIM_LEADER KC_NO\n"); break;
  }
}

/***
 *     #######  #     #  #######       #####   #     #  #######  #######
 *     #     #  ##    #  #            #     #  #     #  #     #     #
 *     #     #  # #   #  #            #        #     #  #     #     #
 *     #     #  #  #  #  #####         #####   #######  #     #     #
 *     #     #  #   # #  #                  #  #     #  #     #     #
 *     #     #  #    ##  #            #     #  #     #  #     #     #
 *     #######  #     #  #######       #####   #     #  #######     #
 *
 */

/**
 * Vim-like `append` command.
 * Works by sending →.
 */
void VIM_APPEND(void) {
  print("VIM_APPEND\n");
  TAP(KC_RIGHT);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `back` command
 * Simulates vim's `b` command by sending ⌥←
 */
void VIM_BACK(void) {
  print("VIM_BACK\n");
  // CTRL(KC_LEFT);
  PRESS(KC_LCTRL);
    TAP(KC_LEFT);
  RELEASE(KC_LCTRL);
}

/**
 * Vim-like `cut` command
 * Simulates vim's `x` command by sending ⇧→ then ⌘X.
 */
void VIM_CUT(void) {
  print("VIM_CUT\n");
  SHIFT(KC_RIGHT);
  CMD(KC_X);
}

/**
 * Vim-like `down` command
 * Sends ↓
 */
void VIM_DOWN(void) {
  print("VIM_DOWN\n");
  TAP(KC_DOWN);
}

/**
 * Vim-like `end` command
 * Simulates vim's `e` command by sending ⌥→
 */
void VIM_END(void) {
  print("VIM_END\n");
  CTRL(KC_RIGHT);
}

/**
 * Vim-like `left` command
 * Sends ←
 */
void VIM_LEFT(void) {
  print("VIM_LEFT\n");
  VIM_LEADER(KC_NO);
  TAP(KC_LEFT);
}

/**
 * Vim-like `open` command.
 * Works by sending ⌘→ to move to the end of the line, `enter` to open a new line,
 * then switching to insert mode.
 */
void VIM_OPEN(void) {
  print("VIM_OPEN\n");
  VIM_LEADER(KC_NO);
  CMD(KC_RIGHT);
  TAP(KC_ENTER);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `put` command
 * Simulates vim's `p` command by sending ⌘V
 */
void VIM_PUT(void) {
  print("VIM_PUT\n");
  VIM_LEADER(KC_NO);
  CMD(KC_V);
}

/**
 * Vim-like `put before` command
 * Simulates vim's `P` command by sending ↑, ⌘←, then ⌘V
 */
void VIM_PUT_BEFORE(bool l_shifted, bool r_shifted) {
  print("VIM_PUT_BEFORE\n");
  VIM_LEADER(KC_NO);
  if (l_shifted) RELEASE(KC_LSHIFT);
  if (r_shifted) RELEASE(KC_RSHIFT);
  TAP(KC_HOME);
  TAP(KC_ENTER);
  TAP(KC_UP);
  CMD(KC_V);
  if (l_shifted) PRESS(KC_LSHIFT);
  if (r_shifted) PRESS(KC_RSHIFT);
}

/**
 * Vim-like `right` command
 * Sends →
 */
void VIM_RIGHT(void) {
  print("VIM_RIGHT\n");
  VIM_LEADER(KC_NO);
  TAP(KC_RIGHT);
}

/**
 * Vim-like `redo` command
 * Simulates vim's `ctrl+r` command by sending ctrl+y
 */
void VIM_REDO(void) {
  print("VIM_REDO\n");
  VIM_LEADER(KC_NO);
  CMD(KC_Y);
}

/**
 * Vim-like `substitute` command
 * Simulates vim's `s` command by sending ⇧→ to select the next character, then
 * ⌘X to cut it, then entering insert mode.
 */
void VIM_SUBSTITUTE(void) {
  print("VIM_SUBSTITUTE\n");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CMD(KC_X);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `undo` command
 * Simulates vim's `u` command by sending ⌘Z
 */
void VIM_UNDO(void) {
  print("VIM_UNDO\n");
  VIM_LEADER(KC_NO);
  CMD(KC_Z);
}

/**
 * Vim-like `up` command
 * Sends ↑
 */
void VIM_UP(void) {
  print("VIM_UP\n");
  VIM_LEADER(KC_NO);
  TAP(KC_UP);
}

/**
 * Vim-like `word` command
 * Simulates vim's `w` command by moving the cursor first to the
 * end of the current word, then to the end of the next word,
 * then to the beginning of that word.
 */
void VIM_WORD(void) {
  print("VIM_WORD\n");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTRL);
    TAP(KC_RIGHT);
    //TAP(KC_RIGHT);
    //TAP(KC_LEFT);
  RELEASE(KC_LCTRL);
}

/**
 * Vim-like `yank` command
 * Simulates vim's `y` command by sending ⌘C
 */
void VIM_YANK(void) {
  print("VIM_YANK\n");
  VIM_LEADER(KC_NO);
  CMD(KC_C);
  TAP(KC_LEFT);
}

/**
 * Vim-like `yank line` command
 * Simulates vim's `y` command by sending ⌘← then ⇧⌘→ then ⌘C
 */
void VIM_YANK_LINE(void) {
  print("VIM_YANK_LINE\n");
  VIM_LEADER(KC_NO);
  CMD(KC_LEFT);
  PRESS(KC_LSHIFT);
    CMD(KC_RIGHT);
  RELEASE(KC_LSHIFT);
  CMD(KC_C);
}

/***
 *      #####   #     #  ###  #######  #######  #######  ######
 *     #     #  #     #   #   #           #     #        #     #
 *     #        #     #   #   #           #     #        #     #
 *      #####   #######   #   #####       #     #####    #     #
 *           #  #     #   #   #           #     #        #     #
 *     #     #  #     #   #   #           #     #        #     #
 *      #####   #     #  ###  #           #     #######  ######
 *
 */

/**
 * Vim-like `append to line` command
 * Simulates vim's `A` command by sending ⌘→ then switching to insert mode.
 */
void VIM_APPEND_LINE(void) {
  print("VIM_APPEND_LINE\n");
  VIM_LEADER(KC_NO);
  CMD(KC_RIGHT);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change line` command
 * Simulates vim's `C` command by sending ⌃K then switching to insert mode.
 */
void VIM_CHANGE_LINE(void) {
  print("VIM_CHANGE_LINE\n");
  VIM_LEADER(KC_NO);
  VIM_DELETE_LINE();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like 'delete line' command
 * Simulates vim's `D` command by sending ⌃K to kill the line
 */
void VIM_DELETE_LINE(void) {
  print("VIM_DELETE_LINE\n");
  VIM_LEADER(KC_NO);
  CTRL(KC_K);
}

/**
 * Vim-like 'join lines' command
 * Simulates vim's `J` command by sending ⌘→ to go to the end of the line, then
 * DELETE to join the lines
 */
void VIM_JOIN(void) {
  print("VIM_JOIN\n");
  VIM_LEADER(KC_NO);
  CMD(KC_RIGHT);
  TAP(KC_DELETE);
  VIM_LEADER(KC_NO);
}

/**
 * Vim-like 'open above' command
 * Simulates vim's `O` command by sending ⌘→ to go to the start of the line,
 * enter to move the line down, ↑ to move up to the new line, then switching to
 * insert mode.
 */
void VIM_OPEN_ABOVE(void) {
  print("VIM_OPEN_ABOVE\n");
  VIM_LEADER(KC_NO);
  CMD(KC_LEFT);
  TAP(KC_ENTER);
  TAP(KC_UP);
  layer_on(INSERT_MODE);
}

/**
 * Vim-like 'change whole line' command
 * Simulates vim's `S` `cc` or `c$` commands by sending ⌘← to go to the start of the line,
 * ⌃K to kill the line, then switching to insert mode.
 */
void VIM_CHANGE_WHOLE_LINE(void) {
  print("VIM_CHANGE_WHOLE_LINE\n");
  VIM_LEADER(KC_NO);
  CMD(KC_LEFT);
  VIM_CHANGE_LINE();
}

/***
 *     ######       ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #      #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #      #     #  #     #  #        #         #     # #    #        #     #
 *     #     #      ######   ######   #####    #####     #      #     #####    #     #
 *     #     #      #        #   #    #        #         #     # #    #        #     #
 *     #     #      #        #    #   #        #         #    #   #   #        #     #
 *     ######       #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `delete to end` command
 * Simulates vim's `de` command by sending ⌥⇧→ then ⌘X.
 */
void VIM_DELETE_END(void) {
  print("VIM_DELETE_END\n");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTRL);
    SHIFT(KC_RIGHT); // select to end of this word
  RELEASE(KC_LCTRL);
  CMD(KC_X);
}

/**
 * Vim-like `delete whole line` command
 * Simulates vim's `dd` command by sending ⌘← to move to start of line,
 * selecting the whole line, then sending ⌘X to cut the line.
 * alternate method: ⌘⌫, ⌃K
 */
void VIM_DELETE_WHOLE_LINE(void) {
  print("VIM_DELETE_WHOLE_LINE\n");
  VIM_LEADER(KC_NO);
  CMD(KC_LEFT);
  PRESS(KC_LSHIFT);
    CMD(KC_RIGHT);
  RELEASE(KC_LSHIFT);
  CMD(KC_X);
}

/**
 * Vim-like `delete word` command
 * Simulates vim's `dw` command by sending ⌥⇧→→← then ⌘X to select to the start
 * of the next word then cut.
 */
void VIM_DELETE_WORD(void) {
  print("VIM_DELETE_WORD\n");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTRL);
    SHIFT(KC_RIGHT); // select to end of this word
    SHIFT(KC_RIGHT); // select to end of next word
    SHIFT(KC_LEFT); // select to start of next word
  RELEASE(KC_LCTRL);
  CMD(KC_X); // delete selection
}

/**
 * Vim-like `delete back` command
 * Simulates vim's `db` command by selecting to the end of the word then deleting.
 */
void VIM_DELETE_BACK(void) {
  print("VIM_DELETE_BACK\n");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTRL);
    SHIFT(KC_LEFT); // select to start of word
    SHIFT(KC_DEL); // delete selection
  RELEASE(KC_LSHIFT);
}

/**
 * Vim-like `delete left` command
 * Simulates vim's `dh` command by sending ⇧← then ⌘X.
 */
void VIM_DELETE_LEFT(void) {
  print("VIM_DELETE_LEFT\n");
  VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
  CMD(KC_X);
}

/**
 * Vim-like `delete right` command
 * Simulates vim's `dl` command by sending ⇧→ then ⌘X.
 */
void VIM_DELETE_RIGHT(void) {
  print("VIM_DELETE_RIGHT\n");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CMD(KC_X);
}

/**
 * Vim-like `delete up` command
 * Simulates vim's `dk` command by sending ↑ then deleting the line.
 */
void VIM_DELETE_UP(void) {
  print("VIM_DELETE_UP\n");
  VIM_LEADER(KC_NO);
  TAP(KC_UP);
  VIM_DELETE_LINE();
}

/**
 * Vim-like `delete down` command
 * Simulates vim's `dj` command by sending ↓ then deleting the line.
 */
void VIM_DELETE_DOWN(void) {
  print("VIM_DELETE_DOWN\n");
  VIM_LEADER(KC_NO);
  TAP(KC_DOWN);
  VIM_DELETE_LINE();
}

/***
 *     ######   ###      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #   #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #   #       #     #  #     #  #        #         #     # #    #        #     #
 *     #     #   #       ######   ######   #####    #####     #      #     #####    #     #
 *     #     #   #       #        #   #    #        #         #     # #    #        #     #
 *     #     #   #       #        #    #   #        #         #    #   #   #        #     #
 *     ######   ###      #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `delete inner word` command
 * Simulates vim's `diw` command by moving back then cutting to the end of the word.
 */
void VIM_DELETE_INNER_WORD(void) {
  print("VIM_DELETE_INNER_WORD\n");
  VIM_LEADER(KC_NO);
  VIM_BACK();
  VIM_DELETE_END();
}

/***
 *      #####        ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #             #     #  #     #  #        #         #     # #    #        #     #
 *     #             ######   ######   #####    #####     #      #     #####    #     #
 *     #             #        #   #    #        #         #     # #    #        #     #
 *     #     #       #        #    #   #        #         #    #   #   #        #     #
 *      #####        #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `change back` command
 * Simulates vim's `cb` command by first deleting to the start of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_BACK(void) {
  print("VIM_CHANGE_BACK\n");
  VIM_LEADER(KC_NO);
  VIM_DELETE_BACK();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change down` command
 * Simulates vim's `cj` command by sending ↓ then changing the line.
 */
void VIM_CHANGE_DOWN(void) {
  print("VIM_CHANGE_DOWN\n");
  VIM_LEADER(KC_NO);
  VIM_DELETE_DOWN();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change to end` command
 * Simulates vim's `ce` command by first deleting to the end of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_END(void) {
  print("VIM_CHANGE_END\n");
  VIM_LEADER(KC_NO);
  VIM_DELETE_END();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change left` command
 * Simulates vim's `ch` command by deleting left then switching to insert mode.
 */
void VIM_CHANGE_LEFT(void) {
  print("VIM_CHANGE_LEFT\n");
  VIM_LEADER(KC_NO);
  VIM_DELETE_LEFT();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change right` command
 * Simulates vim's `cl` command by deleting right then switching to insert mode.
 */
void VIM_CHANGE_RIGHT(void) {
  print("VIM_CHANGE_RIGHT\n");
  VIM_DELETE_RIGHT();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change up` command
 * Simulates vim's `ck` command by deleting up then switching to insert mode.
 */
void VIM_CHANGE_UP(void) {
  print("VIM_CHANGE_UP\n");
  VIM_DELETE_UP();
  layer_on(INSERT_MODE);
}

/**
 * Vim-like `change word` command
 * Simulates vim's `cw` command by first deleting to the end of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_WORD(void) {
  print("VIM_CHANGE_WORD\n");
  VIM_LEADER(KC_NO);
  VIM_DELETE_WORD();
  layer_on(INSERT_MODE);
}

/***
 *      #####   ###      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #   #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #         #       #     #  #     #  #        #         #     # #    #        #     #
 *     #         #       ######   ######   #####    #####     #      #     #####    #     #
 *     #         #       #        #   #    #        #         #     # #    #        #     #
 *     #     #   #       #        #    #   #        #         #    #   #   #        #     #
 *      #####   ###      #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `change inner word` command
 * Simulates vim's `ciw` command by deleting the inner word then switching to insert mode.
 */
void VIM_CHANGE_INNER_WORD(void) {
  print("VIM_CHANGE_INNER_WORD\n");
  VIM_DELETE_INNER_WORD();
  layer_on(INSERT_MODE);
}

/***
 *     #     #      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #      #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #      #     #  #     #  #        #         #     # #    #        #     #
 *     #     #      ######   ######   #####    #####     #      #     #####    #     #
 *      #   #       #        #   #    #        #         #     # #    #        #     #
 *       # #        #        #    #   #        #         #    #   #   #        #     #
 *        #         #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `visual select back` command
 * Simulates vim's `vb` command by selecting to the enc of the word.
 */
void VIM_VISUAL_BACK(void) {
  print("VIM_VISUAL_BACK\n");
  //VIM_LEADER(KC_NO);
  PRESS(KC_LCTRL);
    SHIFT(KC_LEFT); // select to start of word
  RELEASE(KC_LCTRL);
}

/**
 * Vim-like `visual select to end` command
 * Simulates vim's `ve` command by selecting to the end of the word.
 */
void VIM_VISUAL_END(void) {
  print("VIM_VISUAL_END\n");
  // VIM_LEADER(KC_NO);
  PRESS(KC_LCTRL);
    SHIFT(KC_RIGHT); // select to end of this word
  RELEASE(KC_LCTRL);
}

/**
 * Vim-like `visual select word` command
 * Simulates vim's `vw` command by selecting to the end of the word.
 */
void VIM_VISUAL_WORD(void) {
  print("VIM_VISUAL_WORD\n");
  // VIM_LEADER(KC_NO);
  PRESS(KC_LCTRL);
    //SHIFT(KC_RIGHT); // select to end of this word
    SHIFT(KC_RIGHT); // select to end of next word
    //SHIFT(KC_LEFT); // select to start of next word
  RELEASE(KC_LCTRL);
}

/**
 * Vim-like `visual left` command
 * Simulates vim's `vh` command by sending ⇧←.
 */
void VIM_VISUAL_LEFT(void) {
  print("VIM_VISUAL_LEFT\n");
  //VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
}

/**
 * Vim-like `visual right` command
 * Simulates vim's `vl` command by sending ⇧→.
 */
void VIM_VISUAL_RIGHT(void) {
  print("VIM_VISUAL_RIGHT\n");
  //VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
}

/**
 * Vim-like `visual up` command
 * Simulates vim's `vk` command by sending ⇧↑.
 */
void VIM_VISUAL_UP(void) {
  print("VIM_VISUAL_UP\n");
  //VIM_LEADER(KC_NO);
  SHIFT(KC_UP);
}

/**
 * Vim-like `visual down` command
 * Simulates vim's `vj` command by sending ⇧↓.
 */
void VIM_VISUAL_DOWN(void) {
  print("VIM_VISUAL_DOWN\n");
  //VIM_LEADER(KC_NO);
  SHIFT(KC_DOWN);
}

/***
 *     #     #  ###      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #   #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #   #       #     #  #     #  #        #         #     # #    #        #     #
 *     #     #   #       ######   ######   #####    #####     #      #     #####    #     #
 *      #   #    #       #        #   #    #        #         #     # #    #        #     #
 *       # #     #       #        #    #   #        #         #    #   #   #        #     #
 *        #     ###      #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `visual inner word` command
 * Simulates vim's `viw` command by moving back then selecting to the end of the word.
 */
void VIM_VISUAL_INNER_WORD(void) {
  print("VIM_VISUAL_INNER_WORD\n");
  // VIM_LEADER(KC_NO);
  VIM_BACK();
  VIM_VISUAL_END();
}
