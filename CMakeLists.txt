cmake_minimum_required(VERSION 4.0)
project(Helpet)

set(CMAKE_CXX_STANDARD 23)

add_executable(Helpet main.cpp
        src/Person.cpp
        src/Pet.cpp
        src/Vaccine.cpp
        src/Appointment.cpp
        src/AppointmentEnhancer.cpp
        src/BaseAppointment.cpp
        src/Clinic.cpp
        src/ClawTrimmingDecorator.cpp
        src/DentalCareDecorator.cpp
        src/Exception.cpp
        src/GroomingDecorator.cpp
        src/MicroChippingDecorator.cpp
        src/OwnerInput.cpp
        src/Room.cpp
        src/ServiceDecorator.cpp
        src/VaccineStockObserver.cpp
        src/ClinicMenu.cpp
        src/AppointmentService.cpp)

target_include_directories(Helpet PUBLIC include)
