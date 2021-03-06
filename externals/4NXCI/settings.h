#ifndef NXCI_SETTINGS_H
#define NXCI_SETTINGS_H
#include <stdio.h>
#include "types.h"
#include "filepath.h"

extern void throw_runtime_error(int status);

typedef enum {
    KEYSET_DEV,
    KEYSET_RETAIL
} keyset_variant_t;

typedef enum {
    BASEFILE_ROMFS,
    BASEFILE_NCA,
    BASEFILE_FAKE
} nxci_basefile_t;

typedef struct {
    unsigned char secure_boot_key[0x10];                 /* Secure boot key for use in key derivation. NOTE: CONSOLE UNIQUE. */
    unsigned char tsec_key[0x10];                        /* TSEC key for use in key derivation. NOTE: CONSOLE UNIQUE. */
    unsigned char keyblob_keys[0x20][0x10];              /* Actual keys used to decrypt keyblobs. NOTE: CONSOLE UNIQUE.*/
    unsigned char keyblob_mac_keys[0x20][0x10];          /* Keys used to validate keyblobs. NOTE: CONSOLE UNIQUE. */ 
    unsigned char encrypted_keyblobs[0x20][0xB0];        /* Actual encrypted keyblobs (EKS). NOTE: CONSOLE UNIQUE. */ 
    unsigned char keyblobs[0x20][0x90];                  /* Actual decrypted keyblobs (EKS). */ 
    unsigned char keyblob_key_sources[0x20][0x10];       /* Seeds for keyblob keys. */
    unsigned char keyblob_mac_key_source[0x10];          /* Seed for keyblob MAC key derivation. */
    unsigned char master_key_source[0x10];               /* Seed for master key derivation. */
    unsigned char master_keys[0x20][0x10];               /* Firmware master keys. */
    unsigned char package1_keys[0x20][0x10];             /* Package1 keys. */
    unsigned char package2_keys[0x20][0x10];             /* Package2 keys. */
    unsigned char package2_key_source[0x10];             /* Seed for Package2 key. */
    unsigned char aes_kek_generation_source[0x10];       /* Seed for GenerateAesKek, usecase + generation 0. */
    unsigned char aes_key_generation_source[0x10];       /* Seed for GenerateAesKey. */
    unsigned char key_area_key_application_source[0x10]; /* Seed for kaek 0. */
    unsigned char key_area_key_ocean_source[0x10];       /* Seed for kaek 1. */
    unsigned char key_area_key_system_source[0x10];      /* Seed for kaek 2. */
    unsigned char titlekek_source[0x10];                 /* Seed for titlekeks. */
    unsigned char header_kek_source[0x10];               /* Seed for header kek. */
    unsigned char sd_card_kek_source[0x10];              /* Seed for SD card kek. */
    unsigned char sd_card_key_sources[2][0x20];          /* Seed for SD card encryption keys. */
    unsigned char header_key_source[0x20];               /* Seed for NCA header key. */
    unsigned char header_key[0x20];                      /* NCA header key. */
    unsigned char titlekeks[0x20][0x10];                 /* Title key encryption keys. */
    unsigned char key_area_keys[0x20][3][0x10];          /* Key area encryption keys. */
    unsigned char sd_card_keys[2][0x20];
    unsigned char nca_hdr_fixed_key_modulus[0x100];      /* NCA header fixed key RSA pubk. */
    unsigned char acid_fixed_key_modulus[0x100];         /* ACID fixed key RSA pubk. */
    unsigned char package2_fixed_key_modulus[0x100];     /* Package2 Header RSA pubk. */
} nca_keyset_t;

typedef struct {
    int enabled;
    filepath_t path;
} override_filepath_t;

typedef struct {
    uint8_t dummy_tik;
    nca_keyset_t keyset;
    filepath_t section_paths[4];
    filepath_t section_dir_paths[4];
    override_filepath_t out_dir_path;
    filepath_t hfs0_dir_path;
    filepath_t secure_dir_path;
} nxci_settings_t;

enum hactool_file_type
{
    FILETYPE_NCA,
    FILETYPE_PFS0,
    FILETYPE_ROMFS,
    FILETYPE_NCA0_ROMFS,
    FILETYPE_HFS0,
    FILETYPE_XCI,
    FILETYPE_NPDM,
    FILETYPE_PACKAGE1,
    FILETYPE_PACKAGE2,
    FILETYPE_INI1,
    FILETYPE_KIP1,
    FILETYPE_NSO0,
    FILETYPE_NAX0,
    FILETYPE_BOOT0
};


struct nca_ctx; /* This will get re-defined by nca.h. */

typedef struct {
    enum hactool_file_type file_type;
    FILE *file;
    FILE *base_file;
    nxci_basefile_t base_file_type;
    struct nca_ctx *base_nca_ctx;
    nxci_settings_t settings;
    uint32_t action;
} nxci_ctx_t;

#endif
