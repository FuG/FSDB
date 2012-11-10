
#include "testing.h"

clock_t start_time, end_time;
double time_taken;

void stress_setup()
{
	MySQL_Interface interface;
	printf("Setting up a %d pocID x %d sensorID table for stress testing.\n", stress_pocs, stress_sensors_per_poc);
	printf("This may take up to several minutes. Please wait...\n");
	setup_test_table(interface.get_con(), 100, 100);
	printf("Done!\n\n");
}

void stress_test_get_spot_status()
{
	int i = 0;
	int proj_cycles = 0;
	bool result = 0;
	start_time = 0, end_time = 0, time_taken = 0.0;
	MySQL_Interface interface;

	print_stress_f_name("get_spot_status");

	start_t;
	for (i = 0; i < stress_cycles; i++)
	{
		result = interface.get_spot_status(50, 50);
	}
	end_t;
	calc_dif;

	proj_cycles = (int)(60.0 / time_taken * stress_cycles);
	printf("Performed %d x get_spot_status() on a %d-entry table.\n",
			stress_cycles, stress_pocs * stress_sensors_per_poc);
	printf("Time taken: %.3lf seconds.\n", time_taken);
	printf("Max. Function Cycles / Minute: %d\n", proj_cycles);
	printf("\n");
}

void stress_test_set_spot_status()
{
	int i = 0;
	int proj_cycles = 0;
	start_time = 0, end_time = 0, time_taken = 0.0;
	MySQL_Interface interface;

	print_stress_f_name("set_spot_status");

	start_t;
	for (i = 0; i < stress_cycles; i++)
	{
		interface.set_spot_status(50, 50, 1);
	}
	end_t;
	calc_dif;

	proj_cycles = (int)(60.0 / time_taken * stress_cycles);
	printf("Performed %d x set_spot_status() on a %d-entry table.\n",
			stress_cycles, stress_pocs * stress_sensors_per_poc);
	printf("Time taken: %.3lf seconds.\n", time_taken);
	printf("Max. Function Cycles / Minute: %d\n", proj_cycles);
	printf("\n");
}
