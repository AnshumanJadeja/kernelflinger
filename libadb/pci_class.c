/*
 * Copyright (c) 2019, Intel Corporation
 * All rights reserved.
 *
 * Authors: Jeremy Compostella <jeremy.compostella@intel.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "pci_class.h"
#include "log.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

typedef struct {
	UINT8 id;
	char *name;
} assoc_t;

static assoc_t UNCLASSIFIED[] = {
	{ 0x00,	"Non-VGA unclassified device" },
	{ 0x01,	"VGA compatible unclassified device" },
	{ 0xFF, NULL }
};

static assoc_t MASS[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"SCSI storage controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"IDE interface" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"Floppy disk controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03,	"IPI bus controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x04,	"RAID bus controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x05,	"ATA controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x06,	"SATA controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x07,	"Serial Attached SCSI controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x08,	"Non-Volatile memory controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Mass storage controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t NETWORK[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"Ethernet controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"Token ring network controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"FDDI network controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03,	"ATM network controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x04,	"ISDN controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x05,	"WorldFip controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x06,	"PICMG controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x07,	"Infiniband controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x08,	"Fabric controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Network controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t DISPLAY[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"VGA compatible controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"XGA compatible controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"3D controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Display controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t MULTIMEDIA[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"Multimedia video controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"Multimedia audio controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"Computer telephony device" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03,	"Audio device" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Multimedia controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t MEMORY[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"RAM memory" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"FLASH memory" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Memory controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t BRIDGE[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"Host bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"ISA bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"EISA bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03,	"MicroChannel bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x04,	"PCI bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x05,	"PCMCIA bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x06,	"NuBus bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x07,	"CardBus bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x08,	"RACEway bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x09,	"Semi-transparent PCI-to-PCI bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x0a,	"InfiniBand to PCI host bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Bridge" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t SIMPLE[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"Serial controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"Parallel controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"Multiport serial controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03,	"Modem" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x04,	"GPIB controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x05,	"Smard Card controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Communication controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t BASE[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"PIC" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"DMA controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"Timer" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03,	"RTC" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x04,	"PCI Hot-plug controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x05,	"SD Host controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x06,	"IOMMU" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"System peripheral" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t INPUT[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"Keyboard controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"Digitizer Pen" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"Mouse controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03,	"Scanner controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x04,	"Gameport controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Input device controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t DOCKING[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"Generic Docking Station" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Docking Station" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t PROCESSOR[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"386" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"486" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"Pentium" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x10,	"Alpha" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x20,	"Power PC" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x30,	"MIPS" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x40,	"Co-processor" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t SERIAL[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"FireWire (IEEE 1394" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"ACCESS Bus" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"SSA" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03,	"USB controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x04,	"Fibre Channel" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x05,	"SMBus" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x06,	"InfiniBand" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x07,	"IPMI Interface" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x08,	"SERCOS interface" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x09,	"CANBUS" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t WIRELESS[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"IRDA controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"Consumer IR controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x10,	"RF controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x11,	"Bluetooth" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x12,	"Broadband" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x20,	"802.1a controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x21,	"802.1b controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Wireless controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t INTELLIGENT[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"I2O" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t SATELLITE[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"Satellite TV controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02,	"Satellite audio communication controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03,	"Satellite voice communication controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x04,	"Satellite data communication controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t ENCRYPTION[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"Network and computing encryption device" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x10,	"Entertainment encryption device" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Encryption controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t SIGNAL[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"DPIO module" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"Performance counters" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x10,	"Communication synchronizer" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x20,	"Signal processing management" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x80,	"Signal processing controller" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static assoc_t PROCESSING[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00,	"Processing accelerators" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01,	"AI Inference Accelerator" },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0xFF, NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

static const struct {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	UINT8 id;
	char *name;
	assoc_t *subclass;
} CLASSES[] = {
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x00, "Unclassified", (assoc_t *)&UNCLASSIFIED },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x01, "Mass storage controller", (assoc_t *)&MASS },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x02, "Network controller", (assoc_t *)&NETWORK },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x03, "Display controller", (assoc_t *)&DISPLAY },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x04, "Multimedia device", (assoc_t *)&MULTIMEDIA },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x05, "Memory controller", (assoc_t *)&MEMORY },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x06, "Bridge device", (assoc_t *)&BRIDGE },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x07, "Simple communication controllers", (assoc_t *)&SIMPLE },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x08, "Base system peripherals", (assoc_t *)&BASE },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x09, "Input devices", (assoc_t *)&INPUT },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x0A, "Docking stations", (assoc_t *)&DOCKING },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x0B, "Processors", (assoc_t *)&PROCESSOR },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x0C, "Serial bus controllers", (assoc_t *)&SERIAL },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x0D, "Wireless controller", (assoc_t *)&WIRELESS },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x0E, "Intelligent I/O controllers", (assoc_t *)&INTELLIGENT },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x0F, "Satellite communication controllers", (assoc_t *)&SATELLITE },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x10, "Encryption/Decryption controllers", (assoc_t *)&ENCRYPTION },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x11, "Signal processing controllers", (assoc_t *)&SIGNAL },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x12, "Processing accelerators", (assoc_t *)&PROCESSING },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x13, "Non-Essential Instrumentation", NULL },
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	{ 0x40, "Coprocessor", NULL }
  debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
};

const char *pci_class_string(UINT8 base, UINT8 sub)
{
   debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
	UINTN i, j;
	assoc_t *subclass;

	for (i = 0; i < ARRAY_SIZE(CLASSES); i++)
		if (base == CLASSES[i].id) {
     debug(L"INSTRUMENT:%a:%a", __FILE__, __func__);
			subclass = CLASSES[i].subclass;
			if (!subclass)
				return CLASSES[i].name;

			for (j = 0; subclass[j].name; j++)
				if (sub == subclass[j].id)
					return subclass[j].name;

			return CLASSES[i].name;
		}

	return NULL;
}
