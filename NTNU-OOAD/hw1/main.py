import math

class Shape:
    def area(self):
        raise NotImplementedError("Subclasses should implement this method")
    
    def perimeter(self):
        raise NotImplementedError("Subclasses should implement this method")

# Circle class with area and perimeter calculation
class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return math.pi * self.radius ** 2

    def perimeter(self):
        return 2 * math.pi * self.radius

# Rectangle class with area and perimeter calculation
class Rectangle(Shape):
    def __init__(self, length, width):
        self.length = length
        self.width = width

    def __eq__(self, other):
        if not isinstance(other, Rectangle):
            return False
        return self.length == other.length and self.width == other.width

    def area(self):
        return self.length * self.width

    def perimeter(self):
        return 2 * (self.length + self.width)

# Square class, inheriting from Rectangle with area and perimeter calculation
class Square(Rectangle):
    def __init__(self, side_length):
        # Call the __init__ method of Rectangle
        super().__init__(side_length, side_length)

# Now let's create a database for shapes and print out their equations for area and perimeter
class ShapeDatabase:
    def __init__(self):
        self.shapes = []
    
    def add_shape(self, shape):
        if not isinstance(shape, Shape):
            raise TypeError("Only shapes can be added to the database")
        self.shapes.append(shape)
    

    def display_all_shapes(self):
        for shape in self.shapes:
            print("=====================")
            print(f"Shape: ", shape.__class__.__name__)
            print(f"Area: {shape.area()}")
            print(f"Perimeter: {shape.perimeter()}")
            print("=====================\n")

    def sort(self):
         self.shapes.sort(key=lambda shape: shape.area(), reverse=True)

def main():
    # Create a ShapeDatabase instance
    shape_db = ShapeDatabase()
    
    # Add different shapes to the database
    shape_db.add_shape(Rectangle(4, 6))    # Rectangle with length 4 and width 6
    shape_db.add_shape(Square(3))          # Square with side length 3
    shape_db.add_shape(Circle(5))          # Circle with radius 5
    
    # Sort by z-order
    shape_db.sort()

    # Display the equations for area and perimeter of all shapes in the database
    shape_db.display_all_shapes()

if __name__ == "__main__":
    main()