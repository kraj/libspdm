/**
 *  Copyright Notice:
 *  Copyright 2021-2025 DMTF. All rights reserved.
 *  License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
 **/

/** @file
 * Definitions of Data Object Exchange (DOE) in the PCIe Base specification.
 **/

#ifndef PCI_DOE_BINDING_H
#define PCI_DOE_BINDING_H

#pragma pack(1)

/* DOE header
 * The PCIe specification defines the size of a DW as four bytes. */
typedef struct {
    uint16_t vendor_id;
    uint8_t data_object_type;
    uint8_t reserved;
    /* Length of the data object being transferred in number of DW, including the header (2 DW).
     * It only includes bit[0~17], bit[18~31] are reserved.
     * A value of 00000h indicate 2^18 DW == 2^20 bytes. */
    uint32_t length;
    /*uint32_t   data_object_dw[length];*/
} pci_doe_data_object_header_t;

#define PCI_DOE_VENDOR_ID_PCISIG 0x0001

#define PCI_DOE_DATA_OBJECT_TYPE_DOE_DISCOVERY 0x00
#define PCI_DOE_DATA_OBJECT_TYPE_SPDM 0x01
#define PCI_DOE_DATA_OBJECT_TYPE_SECURED_SPDM 0x02

#define PCI_DOE_MAX_SIZE_IN_BYTE 0x00100000
#define PCI_DOE_MAX_SIZE_IN_DW (PCI_DOE_MAX_SIZE_IN_BYTE / 4)

/* DOE Discovery */
typedef struct {
    uint8_t index;
    uint8_t version;
    uint8_t reserved[2];
} pci_doe_discovery_request_t;

typedef struct {
    uint16_t vendor_id;
    uint8_t data_object_type;
    uint8_t next_index;
} pci_doe_discovery_response_t;

/* SPDM Vendor Defined Message for PCI DOE. */

/* PCI Protocol definition. */
typedef struct {
    uint8_t protocol_id;
} pci_protocol_header_t;

#define PCI_PROTOCOL_ID_IDE_KM 0x00

/* Standard ID and Vendor ID for PCISIG */
#define SPDM_STANDARD_ID_PCISIG SPDM_REGISTRY_ID_PCISIG
#define SPDM_VENDOR_ID_PCISIG 0x0001

typedef struct {
    uint16_t standard_id; /* SPDM_STANDARD_ID_PCISIG*/
    uint8_t len;
    uint16_t vendor_id; /* SPDM_VENDOR_ID_PCISIG*/
    uint16_t payload_length;
    pci_protocol_header_t pci_protocol;
} pci_doe_spdm_vendor_defined_header_t;

typedef struct {
    spdm_message_header_t spdm_header;
    /* param1 == RSVD
     * param2 == RSVD */
    pci_doe_spdm_vendor_defined_header_t pci_doe_vendor_header;
/* pci_protocol specific content */
} pci_doe_spdm_vendor_defined_request_t;

typedef struct {
    spdm_message_header_t spdm_header;
    /* param1 == RSVD
     * param2 == RSVD*/
    pci_doe_spdm_vendor_defined_header_t pci_doe_vendor_header;
/* pci_protocol specific content */
} pci_doe_spdm_vendor_defined_response_t;

#pragma pack()

#endif /* PCI_DOE_BINDING_H */
