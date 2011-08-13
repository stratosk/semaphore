/*
 * max8998.h - Voltage regulator driver for the Maxim 8998
 *
 *  Copyright (C) 2009-2010 Samsung Electrnoics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *  Marek Szyprowski <m.szyprowski@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __LINUX_MFD_MAX8998_H
#define __LINUX_MFD_MAX8998_H

#include <linux/regulator/machine.h>

/* MAX 8998 regulator ids */
enum {
	MAX8998_LDO2 = 2,
	MAX8998_LDO3,
	MAX8998_LDO4,
	MAX8998_LDO5,
	MAX8998_LDO6,
	MAX8998_LDO7,
	MAX8998_LDO8,
	MAX8998_LDO9,
	MAX8998_LDO10,
	MAX8998_LDO11,
	MAX8998_LDO12,
	MAX8998_LDO13,
	MAX8998_LDO14,
	MAX8998_LDO15,
	MAX8998_LDO16,
	MAX8998_LDO17,
	MAX8998_BUCK1,
	MAX8998_BUCK2,
	MAX8998_BUCK3,
	MAX8998_BUCK4,
	MAX8998_EN32KHZ_AP,
	MAX8998_EN32KHZ_CP,
	MAX8998_ENVICHG,
	MAX8998_ESAFEOUT1,
	MAX8998_ESAFEOUT2,
};

/**
 * max8998_regulator_data - regulator data
 * @id: regulator id
 * @initdata: regulator init data (contraints, supplies, ...)
 */
struct max8998_regulator_data {
	int				id;
	struct regulator_init_data	*initdata;
};

enum cable_type_t {
	CABLE_TYPE_NONE = 0,
	CABLE_TYPE_USB,
	CABLE_TYPE_AC,
};

/**
 * max8998_adc_table_data
 * @adc_value : max8998 adc value
 * @temperature : temperature(C) * 10
 */
struct max8998_adc_table_data {
	int adc_value;
	int temperature;
};
struct max8998_charger_callbacks {
	void (*set_cable)(struct max8998_charger_callbacks *ptr, enum cable_type_t status);
	bool (*set_esafe)(struct max8998_charger_callbacks *ptr, u8 esafe);
	bool (*get_vdcin)(struct max8998_charger_callbacks *ptr);
};

/**
 * max8998_charger_data - charger data
 * @id: charger id
 * @initdata: charger init data (contraints, supplies, ...)
 * @adc_table: adc_table must be ascending adc value order
 */
struct max8998_charger_data {
	struct power_supply *psy_fuelgauge;
	void (*register_callbacks)(struct max8998_charger_callbacks *ptr);
	struct max8998_adc_table_data *adc_table;
	int adc_array_size;
};

/**
 * struct max8998_board - packages regulator init data
 * @regulators: array of defined regulators
 * @num_regulators: number of regultors used
 * @irq_base: base IRQ number for max8998, required for IRQs
 * @ono: power onoff IRQ number for max8998
 * @buck1_voltage_set[4]: BUCK1 voltage preset
 * @buck2_voltage_set[2]: BUCK2 voltage preset
 * @buck1_set1: BUCK1 gpio pin 1 to set output voltage
 * @buck1_set2: BUCK1 gpio pin 2 to set output voltage
 * @buck2_set3: BUCK2 gpio pin to set output voltage
 */
struct max8998_platform_data {
	struct max8998_regulator_data	*regulators;
	struct max8998_charger_data	*charger;
	int				num_regulators;
	int				irq_base;
	int				ono;
	int                             buck1_voltage_set[4];
	int                             buck2_voltage_set[2];
	int				buck1_set1;
	int				buck1_set2;
	int				buck2_set3;
};

#endif /*  __LINUX_MFD_MAX8998_H */
