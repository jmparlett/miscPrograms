# Names: Jonathan Parlett (jmp586)
# Drexel University 2021
# Class: CS 172
# Date: June 2, 2021

from abc import ABC, abstractmethod




class Automobile(ABC):
    def __init__(self, make, model, year, mileage, value, vin, mpg):
        self.__make = make
        self.__model = model
        self.__year = year
        self.mileage = mileage
        self.__vin = vin
        self.__mpg = mpg
        self.value = value

    def __eq__(self, other):
        if(isinstance(other, Automobile)):
            return (self.__vin == other.getVin() and self.__make == other.getMake() and self.__model == other.getModel() and self.__year == other.getYear() and self.mileage == other.getMileage()) 
        else:
            return False
    def __str__(self):
        return "make: {}\nmodel: {}\nyear: {}\nmileage: {}\nprice: {}\nvin: {}\n".format(self.__make, self.__model, self.__year, self.mileage, self.value, self.__vin)
    
    def getMake(self):
        return self.__make
    
    def getModel(self):
        return self.__model

    def getYear(self):
        return self.__year

    def getMileage(self):
        return self.mileage

    def getVin(self):
        return self.__vin

    def getMpg(self):
        return self.__mpg 
     
    def setMileage(self, mileage):
        self.mileage=mileage

    def getValue(self):
        return self.value

    def setValue(self, value):
        self.value = value

    
    @abstractmethod
    def drive(self):
        pass



class Car(Automobile):
    def __init__(self, make, model, year, mileage, value, vin, mpg, seats):
        super().__init__(make, model, year, mileage, value, vin, mpg) 
        self.__seats = seats

    def getSeats(self):
        return self.__seats

    def drive(self):
        print("The {} is driving and its got {} seats".format(self.getMake(), self.getSeats()))
    
    def __eq__(self, other):
        if(isinstance(other, Car)):
           return (self.getVin()== other.getVin() and self.getMake() == other.getMake() and self.getModel() == other.getModel() and self.getYear() == other.getYear() and self.mileage == other.getMileage() and self.getSeats() == other.getSeats()) 
        else:
           return False
    def __str__(self):
       return "make: {}\nmodel: {}\nyear: {}\nmileage: {}\nprice: {}\nvin: {}\nseats: {}\n".format(self.getMake(), self.getModel(), self.getYear(), self.mileage, self.value, self.getVin(), self.__seats)
    
    #I saw no reason override getters or setters from parent class. Only eq and str were overridden



class Trailer(Automobile):
    def __init__(self, make, model, year, mileage, value, vin, mpg, maxload, width, height, length, axels):
        super().__init__(make, model, year, mileage, value, vin, mpg) 
        self.__maxload = maxload
        self.__width = width
        self.__height = height
        self.__length = length
        self.__axels = axels

    def getAxels(self):
        return self.__axels

    def getWidth(self):
        return self.__width

    def getHeight(self):
        return self.__height

    def getTrailerVolume(self):
        return self.__height * self.__width * self.__length

    def getMaxload(self):
        return self.__maxload

    def drive(self):
        print("The {}lb trailer is driving watch out.".format(self.getTrailerVolume()))

    def __eq__(self, other):
        if(isinstance(other, Trailer)):
           return (self.getVin() == other.getVin() and self.getMake() == other.getMake() and self.getModel() == other.getModel() and self.getYear() == other.getYear() and self.mileage == other.getMileage() and self.getAxels() == other.getAxels() and self.getTrailerVolume() == other.getTrailerVolume()) 
        else:
           return False
        def __str__(self):
            return "make: {}\nmodel: {}\nyear: {}\nmileage: {}\nprice: {}\nvin: {}\naxels: {}\n".format(self.getMake(), self.getModel(), self.getYear(), self.mileage, self.value, self.getVin(), self.__axels)
    
    #I saw no reason override getters or setters from parent class. Only eq and str were overridden




if __name__ == "__main__":
    inventory = [Car("Ford", "Ranger", 1996, 64000, 400, "&%$GG%$DFDFR@#", 6, 2),
     Car("HUAWAI", "Depression", 2021, 120*10**3, 10**6, "&%$GFDFR@#", 6, 12),
     Car("HURPERYAY", "AAAAAAAAAA", 2057, 896969, 1, "CARBON BAD WATER GOOD", 6, 3),
     Trailer("trails", "happy", 2057, 896969, 1, "globalnotwarm", 6, 666, 20, 70, 30,  4),
     Trailer("MEATRAGE", "ITS SO HOT HERE", 2200, 896969, 1, "WHERESTHEGASGONE", 6, 1337, 10, 20, 30, 8)   
    ]

    for i in inventory:
        print(i)
        i.drive()
    
    print(inventory[0],"==",inventory[0],"?", inventory[0]==inventory[0])

    print(inventory[0],"==",inventory[1],"?", inventory[0]==inventory[1])

    print(inventory[-1],"==",inventory[-2],"?", inventory[-1]==inventory[-2])

    print(inventory[-1],"==",inventory[-1],"?", inventory[-1]==inventory[-1])
        
        
this is some stuff id like in file. please write this for me papa c i promise i wont leave you for rust :(