#include "clingo/io/jot.h"
#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main()
{
   init_tap_c_();

   cRecorder* rec = &recorder_c_( 1024 );

   expect_at_c_( jotln_c_( rec, "boah: ", 128, c_c( " >= " ), 12 ) );
   expect_at_c_( jotln_c_( rec, "the result value is: ", bool_c_( true ), "!" ) );

   expect_at_c_( jot_c_( rec,
      "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",  //  13
      "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",  //  26
      "\n",                                                             //  27
      "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_",  //  40
      "\n",                                                             //  41
      "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",  //  54
      "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",  //  67
      "\n",                                                             //  68
      "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_",  //  81
      "\n",                                                             //  82
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,    // 102
      "\n",                                                             // 103
      "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_",  // 116
      "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",  // 129
      "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",  // 142
      "\n",                                                             // 143
      "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_",  // 156
      "\n",                                                             // 157
      "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",  // 170
      "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",  // 183
      "\n",                                                             // 184
      "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_",  // 197
      "\n",                                                             // 198
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,                                     // 208
      "\n",                                                             // 209
      "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_", "+", "_",  // 222
      "\n",                                                             // 223
      "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",  // 236
      "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",  // 249
      "\n",                                                             // 250
      1, 2, 3, 4                                                        // 254
   ) );
   jotln_c_( rec, "the result value is: ", true, "!" );
   jot_c_( rec, "on ", date_tape_c_( date_c( 2024, c_Aug, 23 ) ), "!!!" );

   expect_at_c_( recorded_is_c( rec, "boah: 128 >= 12\n"
                                  "the result value is: true!\n"
                                  "abcdefghijklmnopqrstuvwxyz\n"
                                  "_+_+_+_+_+_+_\n"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
                                  "_+_+_+_+_+_+_\n"
                                  "012345678901234567890\n"
                                  "_+_+_+_+_+_+_abcdefghijklmnopqrstuvwxyz\n"
                                  "_+_+_+_+_+_+_\n"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
                                  "_+_+_+_+_+_+_\n"
                                  "0123456789\n"
                                  "_+_+_+_+_+_+_\n"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
                                  "1234the result value is: true!\n"
                                  "on 2024-08-23!!!" ) );

   println_recorded_c( rec );

   return finish_tap_c_();
}
