/* 
 * Copyright 2012 Jun Wako <wakojun@gmail.com>
 * This file is based on:
 *     LUFA-120219/Demos/Device/Lowlevel/KeyboardMouse
 *     LUFA-120219/Demos/Device/Lowlevel/GenericHID
 */

/*
             LUFA Library
     Copyright (C) Dean Camera, 2012.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2012  Dean Camera (dean [at] fourwalledcubicle [dot] com)
  Copyright 2010  Denver Gingerich (denver [at] ossguy [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

#include "util.h"
#include "report.h"
#include "descriptor.h"

#ifndef USB_MAX_POWER_CONSUMPTION
#define USB_MAX_POWER_CONSUMPTION 500
#endif

/*******************************************************************************
 * HID Report Descriptors
 ******************************************************************************/
const USB_Descriptor_HIDReport_Datatype_t PROGMEM KeyboardReport[] =
{
    HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
    HID_RI_USAGE(8, 0x06), /* Keyboard */
    HID_RI_COLLECTION(8, 0x01), /* Application */
        HID_RI_USAGE_PAGE(8, 0x07), /* Key Codes */
        HID_RI_USAGE_MINIMUM(8, 0xE0), /* Keyboard Left Control */
        HID_RI_USAGE_MAXIMUM(8, 0xE7), /* Keyboard Right GUI */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(8, 0x01),
        HID_RI_REPORT_COUNT(8, 0x08),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_CONSTANT),  /* reserved */

        HID_RI_USAGE_PAGE(8, 0x08), /* LEDs */
        HID_RI_USAGE_MINIMUM(8, 0x01), /* Num Lock */
        HID_RI_USAGE_MAXIMUM(8, 0x05), /* Kana */
        HID_RI_REPORT_COUNT(8, 0x05),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x03),
        HID_RI_OUTPUT(8, HID_IOF_CONSTANT),

        HID_RI_USAGE_PAGE(8, 0x07), /* Keyboard */
        HID_RI_USAGE_MINIMUM(8, 0x00), /* Reserved (no event indicated) */
        HID_RI_USAGE_MAXIMUM(8, 0xFF), /* Keyboard Application */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF),
        HID_RI_REPORT_COUNT(8, 0x06),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_ARRAY | HID_IOF_ABSOLUTE),
    HID_RI_END_COLLECTION(0),
};

#ifdef MOUSE_ENABLE
const USB_Descriptor_HIDReport_Datatype_t PROGMEM MouseReport[] =
{
    HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
    HID_RI_USAGE(8, 0x02), /* Mouse */
    HID_RI_COLLECTION(8, 0x01), /* Application */
        HID_RI_USAGE(8, 0x01), /* Pointer */
        HID_RI_COLLECTION(8, 0x00), /* Physical */

            HID_RI_USAGE_PAGE(8, 0x09), /* Button */
            HID_RI_USAGE_MINIMUM(8, 0x01),  /* Button 1 */
            HID_RI_USAGE_MAXIMUM(8, 0x05),  /* Button 5 */
            HID_RI_LOGICAL_MINIMUM(8, 0x00),
            HID_RI_LOGICAL_MAXIMUM(8, 0x01),
            HID_RI_REPORT_COUNT(8, 0x05),
            HID_RI_REPORT_SIZE(8, 0x01),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x03),
            HID_RI_INPUT(8, HID_IOF_CONSTANT),

            HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
            HID_RI_USAGE(8, 0x30), /* Usage X */
            HID_RI_USAGE(8, 0x31), /* Usage Y */
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x02),
            HID_RI_REPORT_SIZE(8, 0x08),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

            HID_RI_USAGE(8, 0x38), /* Wheel */
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x08),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

            HID_RI_USAGE_PAGE(8, 0x0C), /* Consumer */
            HID_RI_USAGE(16, 0x0238), /* AC Pan (Horizontal wheel) */
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x08),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

        HID_RI_END_COLLECTION(0),
    HID_RI_END_COLLECTION(0),
};
#endif

#ifdef EXTRAKEY_ENABLE
const USB_Descriptor_HIDReport_Datatype_t PROGMEM ExtrakeyReport[] =
{
    HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
    HID_RI_USAGE(8, 0x80), /* System Control */
    HID_RI_COLLECTION(8, 0x01), /* Application */
        HID_RI_REPORT_ID(8, REPORT_ID_SYSTEM),
        HID_RI_LOGICAL_MINIMUM(16, 0x0001),
        HID_RI_LOGICAL_MAXIMUM(16, 0x0003),
        HID_RI_USAGE_MINIMUM(16, 0x0081), /* System Power Down */
        HID_RI_USAGE_MAXIMUM(16, 0x0083), /* System Wake Up */
        HID_RI_REPORT_SIZE(8, 16),
        HID_RI_REPORT_COUNT(8, 1),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_ARRAY | HID_IOF_ABSOLUTE),
    HID_RI_END_COLLECTION(0),

    HID_RI_USAGE_PAGE(8, 0x0C), /* Consumer */
    HID_RI_USAGE(8, 0x01), /* Consumer Control */
    HID_RI_COLLECTION(8, 0x01), /* Application */
        HID_RI_REPORT_ID(8, REPORT_ID_CONSUMER),
        HID_RI_LOGICAL_MINIMUM(16, 0x0001),
        HID_RI_LOGICAL_MAXIMUM(16, 0x029C),
        HID_RI_USAGE_MINIMUM(16, 0x0001), /* +10 */
        HID_RI_USAGE_MAXIMUM(16, 0x029C), /* AC Distribute Vertically */
        HID_RI_REPORT_SIZE(8, 16),
        HID_RI_REPORT_COUNT(8, 1),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_ARRAY | HID_IOF_ABSOLUTE),
    HID_RI_END_COLLECTION(0),
};
#endif

#ifdef RAW_ENABLE
const USB_Descriptor_HIDReport_Datatype_t PROGMEM RawReport[] =
{
    HID_RI_USAGE_PAGE(16, 0xFF60), /* Vendor Page 0xFF60 */
    HID_RI_USAGE(8, 0x61), /* Vendor Usage 0x61 */
    HID_RI_COLLECTION(8, 0x01), /* Application */
        HID_RI_USAGE(8, 0x62), /* Vendor Usage 0x62 */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF),
        HID_RI_REPORT_COUNT(8, RAW_EPSIZE),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        HID_RI_USAGE(8, 0x63), /* Vendor Usage 0x63 */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF),
        HID_RI_REPORT_COUNT(8, RAW_EPSIZE),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
    HID_RI_END_COLLECTION(0),
};
#endif

#ifdef CONSOLE_ENABLE
const USB_Descriptor_HIDReport_Datatype_t PROGMEM ConsoleReport[] =
{
    HID_RI_USAGE_PAGE(16, 0xFF31), /* Vendor Page(PJRC Teensy compatible) */
    HID_RI_USAGE(8, 0x74), /* Vendor Usage(PJRC Teensy compatible) */
    HID_RI_COLLECTION(8, 0x01), /* Application */
        HID_RI_USAGE(8, 0x75), /* Vendor Usage 0x75 */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF),
        HID_RI_REPORT_COUNT(8, CONSOLE_EPSIZE),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
        HID_RI_USAGE(8, 0x76), /* Vendor Usage 0x76 */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(16, 0x00FF),
        HID_RI_REPORT_COUNT(8, CONSOLE_EPSIZE),
        HID_RI_REPORT_SIZE(8, 0x08),
        HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
    HID_RI_END_COLLECTION(0),
};
#endif

#ifdef NKRO_ENABLE
const USB_Descriptor_HIDReport_Datatype_t PROGMEM NKROReport[] =
{
    HID_RI_USAGE_PAGE(8, 0x01), /* Generic Desktop */
    HID_RI_USAGE(8, 0x06), /* Keyboard */
    HID_RI_COLLECTION(8, 0x01), /* Application */
        HID_RI_USAGE_PAGE(8, 0x07), /* Key Codes */
        HID_RI_USAGE_MINIMUM(8, 0xE0), /* Keyboard Left Control */
        HID_RI_USAGE_MAXIMUM(8, 0xE7), /* Keyboard Right GUI */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(8, 0x01),
        HID_RI_REPORT_COUNT(8, 0x08),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

        HID_RI_USAGE_PAGE(8, 0x08), /* LEDs */
        HID_RI_USAGE_MINIMUM(8, 0x01), /* Num Lock */
        HID_RI_USAGE_MAXIMUM(8, 0x05), /* Kana */
        HID_RI_REPORT_COUNT(8, 0x05),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_OUTPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE | HID_IOF_NON_VOLATILE),
        HID_RI_REPORT_COUNT(8, 0x01),
        HID_RI_REPORT_SIZE(8, 0x03),
        HID_RI_OUTPUT(8, HID_IOF_CONSTANT),

        HID_RI_USAGE_PAGE(8, 0x07), /* Key Codes */
        HID_RI_USAGE_MINIMUM(8, 0x00), /* Keyboard 0 */
        HID_RI_USAGE_MAXIMUM(8, (NKRO_EPSIZE-1)*8-1), /* Keyboard Right GUI */
        HID_RI_LOGICAL_MINIMUM(8, 0x00),
        HID_RI_LOGICAL_MAXIMUM(8, 0x01),
        HID_RI_REPORT_COUNT(8, (NKRO_EPSIZE-1)*8),
        HID_RI_REPORT_SIZE(8, 0x01),
        HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),
    HID_RI_END_COLLECTION(0),
};
#endif

/*******************************************************************************
 * Device Descriptors
 ******************************************************************************/
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
    .Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

    .USBSpecification       = VERSION_BCD(1,1,0),
#if VIRTSER_ENABLE
    .Class                  = USB_CSCP_IADDeviceClass,
    .SubClass               = USB_CSCP_IADDeviceSubclass,
    .Protocol               = USB_CSCP_IADDeviceProtocol,
#else
    .Class                  = USB_CSCP_NoDeviceClass,
    .SubClass               = USB_CSCP_NoDeviceSubclass,
    .Protocol               = USB_CSCP_NoDeviceProtocol,
#endif

    .Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

    /* specified in config.h */
    .VendorID               = VENDOR_ID,
    .ProductID              = PRODUCT_ID,
    .ReleaseNumber          = DEVICE_VER,

    .ManufacturerStrIndex   = 0x01,
    .ProductStrIndex        = 0x02,
    .SerialNumStrIndex      = NO_DESCRIPTOR,

    .NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/*******************************************************************************
 * Configuration Descriptors
 ******************************************************************************/
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
    .Config =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

            .TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
            .TotalInterfaces        = TOTAL_INTERFACES,

            .ConfigurationNumber    = 1,
            .ConfigurationStrIndex  = NO_DESCRIPTOR,

            .ConfigAttributes       = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_REMOTEWAKEUP),

            .MaxPowerConsumption    = USB_CONFIG_POWER_MA(USB_MAX_POWER_CONSUMPTION)
        },

    /*
     * Keyboard
     */
    .Keyboard_Interface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = KEYBOARD_INTERFACE,
            .AlternateSetting       = 0x00,

            .TotalEndpoints         = 1,

            .Class                  = HID_CSCP_HIDClass,
            .SubClass               = HID_CSCP_BootSubclass,
            .Protocol               = HID_CSCP_KeyboardBootProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .Keyboard_HID =
        {
            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

            .HIDSpec                = VERSION_BCD(1,1,1),
            .CountryCode            = 0x00,
            .TotalReportDescriptors = 1,
            .HIDReportType          = HID_DTYPE_Report,
            .HIDReportLength        = sizeof(KeyboardReport)
        },

    .Keyboard_INEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = (ENDPOINT_DIR_IN | KEYBOARD_IN_EPNUM),
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = KEYBOARD_EPSIZE,
            .PollingIntervalMS      = 0x0A
        },

    /*
     * Mouse
     */
#ifdef MOUSE_ENABLE
    .Mouse_Interface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = MOUSE_INTERFACE,
            .AlternateSetting       = 0x00,

            .TotalEndpoints         = 1,

            .Class                  = HID_CSCP_HIDClass,
            .SubClass               = HID_CSCP_BootSubclass,
            .Protocol               = HID_CSCP_MouseBootProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .Mouse_HID =
        {
            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

            .HIDSpec                = VERSION_BCD(1,1,1),
            .CountryCode            = 0x00,
            .TotalReportDescriptors = 1,
            .HIDReportType          = HID_DTYPE_Report,
            .HIDReportLength        = sizeof(MouseReport)
        },

    .Mouse_INEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = (ENDPOINT_DIR_IN | MOUSE_IN_EPNUM),
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = MOUSE_EPSIZE,
            .PollingIntervalMS      = 0x0A
        },
#endif

    /*
     * Extra
     */
#ifdef EXTRAKEY_ENABLE
    .Extrakey_Interface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = EXTRAKEY_INTERFACE,
            .AlternateSetting       = 0x00,

            .TotalEndpoints         = 1,

            .Class                  = HID_CSCP_HIDClass,
            .SubClass               = HID_CSCP_NonBootSubclass,
            .Protocol               = HID_CSCP_NonBootProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .Extrakey_HID =
        {
            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

            .HIDSpec                = VERSION_BCD(1,1,1),
            .CountryCode            = 0x00,
            .TotalReportDescriptors = 1,
            .HIDReportType          = HID_DTYPE_Report,
            .HIDReportLength        = sizeof(ExtrakeyReport)
        },

    .Extrakey_INEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = (ENDPOINT_DIR_IN | EXTRAKEY_IN_EPNUM),
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = EXTRAKEY_EPSIZE,
            .PollingIntervalMS      = 0x0A
        },
#endif

		/*
	     * Raw
	     */
	#ifdef RAW_ENABLE
	    .Raw_Interface =
	        {
	            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

	            .InterfaceNumber        = RAW_INTERFACE,
	            .AlternateSetting       = 0x00,

	            .TotalEndpoints         = 2,

	            .Class                  = HID_CSCP_HIDClass,
	            .SubClass               = HID_CSCP_NonBootSubclass,
	            .Protocol               = HID_CSCP_NonBootProtocol,

	            .InterfaceStrIndex      = NO_DESCRIPTOR
	        },

	    .Raw_HID =
	        {
	            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

	            .HIDSpec                = VERSION_BCD(1,1,1),
	            .CountryCode            = 0x00,
	            .TotalReportDescriptors = 1,
	            .HIDReportType          = HID_DTYPE_Report,
	            .HIDReportLength        = sizeof(RawReport)
	        },

	    .Raw_INEndpoint =
	        {
	            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

	            .EndpointAddress        = (ENDPOINT_DIR_IN | RAW_IN_EPNUM),
	            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
	            .EndpointSize           = RAW_EPSIZE,
	            .PollingIntervalMS      = 0x01
	        },

	    .Raw_OUTEndpoint =
	        {
	            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

	            .EndpointAddress        = (ENDPOINT_DIR_OUT | RAW_OUT_EPNUM),
	            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
	            .EndpointSize           = RAW_EPSIZE,
	            .PollingIntervalMS      = 0x01
	        },
	#endif

    /*
     * Console
     */
#ifdef CONSOLE_ENABLE
    .Console_Interface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = CONSOLE_INTERFACE,
            .AlternateSetting       = 0x00,

            .TotalEndpoints         = 2,

            .Class                  = HID_CSCP_HIDClass,
            .SubClass               = HID_CSCP_NonBootSubclass,
            .Protocol               = HID_CSCP_NonBootProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .Console_HID =
        {
            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

            .HIDSpec                = VERSION_BCD(1,1,1),
            .CountryCode            = 0x00,
            .TotalReportDescriptors = 1,
            .HIDReportType          = HID_DTYPE_Report,
            .HIDReportLength        = sizeof(ConsoleReport)
        },

    .Console_INEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = (ENDPOINT_DIR_IN | CONSOLE_IN_EPNUM),
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = CONSOLE_EPSIZE,
            .PollingIntervalMS      = 0x01
        },

    .Console_OUTEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = (ENDPOINT_DIR_OUT | CONSOLE_OUT_EPNUM),
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = CONSOLE_EPSIZE,
            .PollingIntervalMS      = 0x01
        },
#endif

    /*
     * NKRO
     */
#ifdef NKRO_ENABLE
    .NKRO_Interface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = NKRO_INTERFACE,
            .AlternateSetting       = 0x00,

            .TotalEndpoints         = 1,

            .Class                  = HID_CSCP_HIDClass,
            .SubClass               = HID_CSCP_NonBootSubclass,
            .Protocol               = HID_CSCP_NonBootProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    .NKRO_HID =
        {
            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

            .HIDSpec                = VERSION_BCD(1,1,1),
            .CountryCode            = 0x00,
            .TotalReportDescriptors = 1,
            .HIDReportType          = HID_DTYPE_Report,
            .HIDReportLength        = sizeof(NKROReport)
        },

    .NKRO_INEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = (ENDPOINT_DIR_IN | NKRO_IN_EPNUM),
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = NKRO_EPSIZE,
            .PollingIntervalMS      = 0x01
        },
#endif

#ifdef MIDI_ENABLE
    .Audio_ControlInterface =
        {
            .Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber          = AC_INTERFACE,
            .AlternateSetting         = 0,

            .TotalEndpoints           = 0,

            .Class                    = AUDIO_CSCP_AudioClass,
            .SubClass                 = AUDIO_CSCP_ControlSubclass,
            .Protocol                 = AUDIO_CSCP_ControlProtocol,

            .InterfaceStrIndex        = NO_DESCRIPTOR
        },

    .Audio_ControlInterface_SPC =
        {
            .Header                   = {.Size = sizeof(USB_Audio_Descriptor_Interface_AC_t), .Type = DTYPE_CSInterface},
            .Subtype                  = AUDIO_DSUBTYPE_CSInterface_Header,

            .ACSpecification          = VERSION_BCD(1,0,0),
            .TotalLength              = sizeof(USB_Audio_Descriptor_Interface_AC_t),

            .InCollection             = 1,
            .InterfaceNumber          = AS_INTERFACE,
        },

    .Audio_StreamInterface =
        {
            .Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber          = AS_INTERFACE,
            .AlternateSetting         = 0,

            .TotalEndpoints           = 2,

            .Class                    = AUDIO_CSCP_AudioClass,
            .SubClass                 = AUDIO_CSCP_MIDIStreamingSubclass,
            .Protocol                 = AUDIO_CSCP_StreamingProtocol,

            .InterfaceStrIndex        = NO_DESCRIPTOR
        },

    .Audio_StreamInterface_SPC =
        {
            .Header                   = {.Size = sizeof(USB_MIDI_Descriptor_AudioInterface_AS_t), .Type = DTYPE_CSInterface},
            .Subtype                  = AUDIO_DSUBTYPE_CSInterface_General,

            .AudioSpecification       = VERSION_BCD(1,0,0),

            .TotalLength              = (sizeof(USB_Descriptor_Configuration_t) -
                                         offsetof(USB_Descriptor_Configuration_t, Audio_StreamInterface_SPC))
        },

    .MIDI_In_Jack_Emb =
        {
            .Header                   = {.Size = sizeof(USB_MIDI_Descriptor_InputJack_t), .Type = DTYPE_CSInterface},
            .Subtype                  = AUDIO_DSUBTYPE_CSInterface_InputTerminal,

            .JackType                 = MIDI_JACKTYPE_Embedded,
            .JackID                   = 0x01,

            .JackStrIndex             = NO_DESCRIPTOR
        },

    .MIDI_In_Jack_Ext =
        {
            .Header                   = {.Size = sizeof(USB_MIDI_Descriptor_InputJack_t), .Type = DTYPE_CSInterface},
            .Subtype                  = AUDIO_DSUBTYPE_CSInterface_InputTerminal,

            .JackType                 = MIDI_JACKTYPE_External,
            .JackID                   = 0x02,

            .JackStrIndex             = NO_DESCRIPTOR
        },

    .MIDI_Out_Jack_Emb =
        {
            .Header                   = {.Size = sizeof(USB_MIDI_Descriptor_OutputJack_t), .Type = DTYPE_CSInterface},
            .Subtype                  = AUDIO_DSUBTYPE_CSInterface_OutputTerminal,

            .JackType                 = MIDI_JACKTYPE_Embedded,
            .JackID                   = 0x03,

            .NumberOfPins             = 1,
            .SourceJackID             = {0x02},
            .SourcePinID              = {0x01},

            .JackStrIndex             = NO_DESCRIPTOR
        },

    .MIDI_Out_Jack_Ext =
        {
            .Header                   = {.Size = sizeof(USB_MIDI_Descriptor_OutputJack_t), .Type = DTYPE_CSInterface},
            .Subtype                  = AUDIO_DSUBTYPE_CSInterface_OutputTerminal,

            .JackType                 = MIDI_JACKTYPE_External,
            .JackID                   = 0x04,

            .NumberOfPins             = 1,
            .SourceJackID             = {0x01},
            .SourcePinID              = {0x01},

            .JackStrIndex             = NO_DESCRIPTOR
        },

    .MIDI_In_Jack_Endpoint =
        {
            .Endpoint =
                {
                    .Header              = {.Size = sizeof(USB_Audio_Descriptor_StreamEndpoint_Std_t), .Type = DTYPE_Endpoint},

                    .EndpointAddress     = MIDI_STREAM_OUT_EPADDR,
                    .Attributes          = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
                    .EndpointSize        = MIDI_STREAM_EPSIZE,
                    .PollingIntervalMS   = 0x05
                },

            .Refresh                  = 0,
            .SyncEndpointNumber       = 0
        },

    .MIDI_In_Jack_Endpoint_SPC =
        {
            .Header                   = {.Size = sizeof(USB_MIDI_Descriptor_Jack_Endpoint_t), .Type = DTYPE_CSEndpoint},
            .Subtype                  = AUDIO_DSUBTYPE_CSEndpoint_General,

            .TotalEmbeddedJacks       = 0x01,
            .AssociatedJackID         = {0x01}
        },

    .MIDI_Out_Jack_Endpoint =
        {
            .Endpoint =
                {
                    .Header              = {.Size = sizeof(USB_Audio_Descriptor_StreamEndpoint_Std_t), .Type = DTYPE_Endpoint},

                    .EndpointAddress     = MIDI_STREAM_IN_EPADDR,
                    .Attributes          = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
                    .EndpointSize        = MIDI_STREAM_EPSIZE,
                    .PollingIntervalMS   = 0x05
                },

            .Refresh                  = 0,
            .SyncEndpointNumber       = 0
        },

    .MIDI_Out_Jack_Endpoint_SPC =
        {
            .Header                   = {.Size = sizeof(USB_MIDI_Descriptor_Jack_Endpoint_t), .Type = DTYPE_CSEndpoint},
            .Subtype                  = AUDIO_DSUBTYPE_CSEndpoint_General,

            .TotalEmbeddedJacks       = 0x01,
            .AssociatedJackID         = {0x03}
        },
#endif

#ifdef VIRTSER_ENABLE
    .CDC_Interface_Association =
            {
                    .Header                 = {.Size = sizeof(USB_Descriptor_Interface_Association_t), .Type = DTYPE_InterfaceAssociation},

                    .FirstInterfaceIndex    = CCI_INTERFACE,
                    .TotalInterfaces        = 2,

                    .Class                  = CDC_CSCP_CDCClass,
                    .SubClass               = CDC_CSCP_ACMSubclass,
                    .Protocol               = CDC_CSCP_ATCommandProtocol,

                    .IADStrIndex            = NO_DESCRIPTOR,
            },

    .CDC_CCI_Interface =
            {
                    .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

                    .InterfaceNumber        = CCI_INTERFACE,
                    .AlternateSetting       = 0,

                    .TotalEndpoints         = 1,

                    .Class                  = CDC_CSCP_CDCClass,
                    .SubClass               = CDC_CSCP_ACMSubclass,
                    .Protocol               = CDC_CSCP_ATCommandProtocol,

                    .InterfaceStrIndex      = NO_DESCRIPTOR
            },

    .CDC_Functional_Header =
            {
                    .Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalHeader_t), .Type = DTYPE_CSInterface},
                    .Subtype                = 0x00,

                    .CDCSpecification       = VERSION_BCD(1,1,0),
            },

    .CDC_Functional_ACM =
            {
                    .Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalACM_t), .Type = DTYPE_CSInterface},
                    .Subtype                = 0x02,

                    .Capabilities           = 0x02,
            },

    .CDC_Functional_Union =
            {
                    .Header                 = {.Size = sizeof(USB_CDC_Descriptor_FunctionalUnion_t), .Type = DTYPE_CSInterface},
                    .Subtype                = 0x06,

                    .MasterInterfaceNumber  = CCI_INTERFACE,
                    .SlaveInterfaceNumber   = CDI_INTERFACE,
            },

    .CDC_NotificationEndpoint =
            {
                    .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

                    .EndpointAddress        = CDC_NOTIFICATION_EPADDR,
                    .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
                    .EndpointSize           = CDC_NOTIFICATION_EPSIZE,
                    .PollingIntervalMS      = 0xFF
            },

    .CDC_DCI_Interface =
            {
                    .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

                    .InterfaceNumber        = CDI_INTERFACE,
                    .AlternateSetting       = 0,

                    .TotalEndpoints         = 2,

                    .Class                  = CDC_CSCP_CDCDataClass,
                    .SubClass               = CDC_CSCP_NoDataSubclass,
                    .Protocol               = CDC_CSCP_NoDataProtocol,

                    .InterfaceStrIndex      = NO_DESCRIPTOR
            },

    .CDC_DataOutEndpoint =
            {
                    .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

                    .EndpointAddress        = CDC_OUT_EPADDR,
                    .Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
                    .EndpointSize           = CDC_EPSIZE,
                    .PollingIntervalMS      = 0x05
            },

    .CDC_DataInEndpoint =
            {
                    .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

                    .EndpointAddress        = CDC_IN_EPADDR,
                    .Attributes             = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
                    .EndpointSize           = CDC_EPSIZE,
                    .PollingIntervalMS      = 0x05
            },
#endif
};


/*******************************************************************************
 * String Descriptors
 ******************************************************************************/
const USB_Descriptor_String_t PROGMEM LanguageString =
{
    .Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

    .UnicodeString          = {LANGUAGE_ID_ENG}
};

const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
    /* subtract 1 for null terminator */
    .Header                 = {.Size = USB_STRING_LEN(sizeof(STR(MANUFACTURER))-1), .Type = DTYPE_String},

    .UnicodeString          = LSTR(MANUFACTURER)
};

const USB_Descriptor_String_t PROGMEM ProductString =
{
    /* subtract 1 for null terminator */
    .Header                 = {.Size = USB_STRING_LEN(sizeof(STR(PRODUCT))-1), .Type = DTYPE_String},

    .UnicodeString          = LSTR(PRODUCT)
};


/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint8_t wIndex,
                                    const void** const DescriptorAddress)
{
    const uint8_t  DescriptorType   = (wValue >> 8);
    const uint8_t  DescriptorIndex  = (wValue & 0xFF);

    const void* Address = NULL;
    uint16_t    Size    = NO_DESCRIPTOR;

    switch (DescriptorType)
    {
        case DTYPE_Device:
            Address = &DeviceDescriptor;
            Size    = sizeof(USB_Descriptor_Device_t);
            break;
        case DTYPE_Configuration:
            Address = &ConfigurationDescriptor;
            Size    = sizeof(USB_Descriptor_Configuration_t);
            break;
        case DTYPE_String:
            switch (DescriptorIndex )
            {
                case 0x00:
                    Address = &LanguageString;
                    Size    = pgm_read_byte(&LanguageString.Header.Size);
                    break;
                case 0x01:
                    Address = &ManufacturerString;
                    Size    = pgm_read_byte(&ManufacturerString.Header.Size);
                    break;
                case 0x02:
                    Address = &ProductString;
                    Size    = pgm_read_byte(&ProductString.Header.Size);
                    break;
            }
            break;
        case HID_DTYPE_HID:
            switch (wIndex) {
            case KEYBOARD_INTERFACE:
                Address = &ConfigurationDescriptor.Keyboard_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#ifdef MOUSE_ENABLE
            case MOUSE_INTERFACE:
                Address = &ConfigurationDescriptor.Mouse_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#endif
#ifdef EXTRAKEY_ENABLE
            case EXTRAKEY_INTERFACE:
                Address = &ConfigurationDescriptor.Extrakey_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#endif
#ifdef RAW_ENABLE
            case RAW_INTERFACE:
                Address = &ConfigurationDescriptor.Raw_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#endif
#ifdef CONSOLE_ENABLE
            case CONSOLE_INTERFACE:
                Address = &ConfigurationDescriptor.Console_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#endif
#ifdef NKRO_ENABLE
            case NKRO_INTERFACE:
                Address = &ConfigurationDescriptor.NKRO_HID;
                Size    = sizeof(USB_HID_Descriptor_HID_t);
                break;
#endif
            }
            break;
        case HID_DTYPE_Report:
            switch (wIndex) {
            case KEYBOARD_INTERFACE:
                Address = &KeyboardReport;
                Size    = sizeof(KeyboardReport);
                break;
#ifdef MOUSE_ENABLE
            case MOUSE_INTERFACE:
                Address = &MouseReport;
                Size    = sizeof(MouseReport);
                break;
#endif
#ifdef EXTRAKEY_ENABLE
            case EXTRAKEY_INTERFACE:
                Address = &ExtrakeyReport;
                Size    = sizeof(ExtrakeyReport);
                break;
#endif
#ifdef RAW_ENABLE
            case RAW_INTERFACE:
                Address = &RawReport;
                Size    = sizeof(RawReport);
                break;
#endif
#ifdef CONSOLE_ENABLE
            case CONSOLE_INTERFACE:
                Address = &ConsoleReport;
                Size    = sizeof(ConsoleReport);
                break;
#endif
#ifdef NKRO_ENABLE
            case NKRO_INTERFACE:
                Address = &NKROReport;
                Size    = sizeof(NKROReport);
                break;
#endif
            }
            break;
    }

    *DescriptorAddress = Address;
    return Size;
}
