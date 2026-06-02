.. zephyr:code-sample:: tfm_secure_peripheral
   :name: TF-M Secure Peripheral

   Create a secure partition that pilots a secure peripheral (LED).

Overview
********

A Secure Partition is an isolated module that resides in TF-M. It exposes a number of functions or
"secure services" to other partitions and/or to the non-secure firmware. TF-M already contains
standard partitions such as crypto, protected_storage, or firmware_update, but it's also possible to
create your own partitions.

This sample creates a secure partition and secure service for TF-M and instructs the TF-M
build system to build it into the secure firmware. The secure service (toggle led) is then called
in the main file (in the non-secure firmware) to toggle an LED on the board.

This partition has a single secure service, which toggles an LED from the SPE. It aims to demonstrate
how to deal with GPIOs from a secure partition, and how to call a secure service from the non-secure firmware.

The partition is located in the ``led_partition`` folder, and the non-secure application is located in the ``src`` folder.
The partition is build by the TF-M build system, refer to :ref:`tfm_build_system` for more details.

For more information on how to add custom secure partitions refer to TF-M's guide:
https://tf-m.docs.trustedfirmware.org/en/latest/integration_guide/services/tfm_secure_partition_addition.html

Building and Running
********************

On Target
=========

To build and run the sample on target, please use b_u585i-iot02a as the target board, and run the following command:

.. code-block:: console

    west build -p always -b b_u585i_iot02a/stm32u585xx/ns
    ./build/tfm/api_ns/regression.sh
    west flash

Sample Output
=============

    .. code-block:: console

        *** Booting Zephyr OS build v4.4.0-3756-ge4fe2cf94263 ***
        NSPE: toggling secure LED (LD7/PH7) via TF-M partition
