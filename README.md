# Helpet: Veterinary Clinic Management System

## 📄 Description

Helpet is a C++ console application designed to simulate the core appointment and service management functionalities of
a veterinary clinic. The application loads initial data (appointments) from a file resources/appointments.in and
provides a menu-based interface for interaction.

## 💻 Technologies Used

* **Language:** C++ (C++23)
* **Build System:** CMake
* **Development IDE:** CLion

## 📂 Project Structure

* `/include`: Contains all header files (`.h`).
* `/src`: Contains all implementation files (`.cpp`). This logic is kept separate from the headers.
* `/resources`: Stores all non-code data assets, such as the `appointments.in` file.
* `CMakeLists.txt`: A single, clean build script manages all dependencies and targets.

## ✨ Features

* **Comprehensive Appointment Management:** Allows users to create, load, display, and manage all clinic appointments,
  verifying real-time doctor and room availability.
* **Administrative Data Access:** Provides access to essential administrative details, including lists of doctors,
  available rooms, and vaccine inventory.
* **Species-Specific Medical Logic:** Implements business logic such as matching appropriate vaccination protocols based
  on the pet's species.
* **Menu-Driven Interface:** A simple console UI for easy navigation through all functionalities.

## 🚀 Build and Run Instructions

This project is configured to be built with CMake and is best run using CLion.

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/georgiana-raluca-negru/Object-Oriented-Programming-1](https://github.com/georgiana-raluca-negru/Object-Oriented-Programming-1)
   ```

2. **Open in CLion:**
    * Open the project folder directly in CLion.
    * Wait for the CMake project to load.

3. **Set the Working Directory (Crucial Step):**
    * The application loads data from the `/resources` folder, therefore the working directory must be set to the
      project root.
    * Go to **Run > Edit Configurations...**
    * In the **"Working directory"** field, set the value to: `$ProjectFileDir$`

4. **Run:**
    * Press the "Run" button to build and execute the application.

## 💡 OOP Concepts Integrated

### 1. Decorator Pattern

* **Purpose:** To add multiple services (e.g., grooming, dental care, microchipping) to a base appointment dynamically.
* **Implementation:** An abstract class `ServiceDecorator` inherits from a common base (`AppointmentService`). Concrete
  classes like `ClawTrimmingDecorator`, `GroomingDecorator` "wrap" the base appointment, adding their cost and
  description
  without modifying the original object.

### 2. Observer Pattern

* **Purpose:** To create a one-to-many dependency for resource tracking, ensuring that parts of the system are
  automatically notified of changes.
* **Implementation:** A `VaccineStock` (Subject) class maintains a list of `Observers`. When the stock level changes, it
  notifies all registered observers (`VaccineStockObserver`) via notify() and logs an alert.

### 3. Polymorphism & Virtual Functions

* **Example:** The `BaseAppointment` base class defines pure virtual functions (e.g.,
  getCost()), forcing derived classes (`ServiceDecorator`, `ClawTrimmingDecorator`) to implement them. This allows for
  uniform handling of different service types.

### 4. Encapsulation

* **Example:** All classes (`Pet`, `Person`, `Clinic`) hide their member data (making them private or protected) and
  provide access through public methods (getters and setters), respecting the "data hiding" principle.

### 5. Exception Handling

* A custom `Exception` class hierarchy is used to handle runtime errors, such as failing to load the
  `resources/appointments.in` file.
