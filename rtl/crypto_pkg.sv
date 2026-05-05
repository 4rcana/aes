package crypto_pkg;

    typedef enum int {
        SBOX_LUT        = 0,
        SBOX_CANRIGHT   = 1
    } sbox_arch_t;

    typedef enum int {
        DIR_FORWARD = 0,
        DIR_INVERSE = 1,
        DIR_SHARED  = 2
    } round_dir_t;

    typedef enum int {
        DUPLEX_HALF = 0,
        DUPLEX_FULL = 1
    } duplex_t;

    typedef enum int {
        AES_ECB = 0,
        AES_CBC = 1
    } aes_mode_t;

endpackage
