This project is a taxi system where drivers can take an order and customers can get to
specific location. This project uses text files as a database. Custom text file reflects drivers
and passengers using the app. Information is permanently stored in this file, even if
the program is not running. The orders text file is a list of orders that appear when
the application is running. Each user must log in to the application and as they work with this
the application is authenticated to ensure that there are no unauthorized logins. To create unique
situations, a randomizer is used.

Each driver can have several vehicles, and they can only be used to transport passengers if
auto checked by the administrator. The driver can remove and add his own vehicles. Everything
the tested cars are stored in the database (cars.txt file). In order to
the car will become available for verification by the administrator, the driver makes a request,
which is stored in the requests.txt database.

A user can have multiple devices. Each of them will be connected to the application. Everyone
the device has a unique MAC address. If the user has not connected the device, he cannot
use the functions of the application. All connected devices are stored in the database
(file devices.txt).

The administrator has the functions of blocking some user capabilities and is engaged in
checking drivers' cars. Thus, the administrator can block the function of receiving
an order from the driver and a trip order from a passenger. User access is stored in their
the respective databases (accessDrivers.txt and accessPassengers.txt). Also when checking the car
it randomly determines if the vehicle is validated. If the car passed the test, then it
adds it to the database. The administrator carries out all his actions through AdminGateway.