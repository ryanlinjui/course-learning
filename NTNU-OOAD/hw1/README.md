# 物件導向分析與設計 HW01
#### 組員: 
- 林昕鋭 41047035S
- 王關平 41047041S
- 陳威豪 NTUST_m11103607
- 陳昱亨 40847030S

## 1. Question
### (a) (15 points) Abstraction

Abstraction refers to the set of concepts that some entity provides you in order for you to achieve a task or solve aproblem.

- **定義:** abstraction主要的定義是隱藏複雜的實現細節，同時只暴露必要的部分。在OO中，abstraction是通過使用class來實現的，這些class定義了abstraction的數據類型或接口，允許用戶以簡化的方式與對象互動，而不需要了解內部運作。使開發人員能夠專注於更高層級的交互，而不是詳細的、逐步的實現。
- **好的抽象化的例子：**
在以下這個例子中，Vehicle是一個abstraction基類，它定義了drive和refuel兩個abstraction。Car類繼承自Vehicle並實現了這些方法。這種方式很好地使用了abstraction，因為它隱藏了具體的實現細節，只暴露了與汽車操作相關的接口。以下為代碼具體解釋 

    基礎抽象類別（Vehicle）：Vehicle類作為一個抽象基礎類別（ABC，即Abstract Base Class），定義了所有車輛共有的基本特性和行為。這包括構造函數（__init__）設置車輛的品牌（make）和型號（model），以及兩個抽象方法：drive()和refuel()。這意味著任何繼承自Vehicle的類都必須實現這些方法，但具體的實現細節留給子類去定義。

        1.抽象方法強制實現：通過將drive和refuel方法標記為抽象方法（@abstractmethod），這強制要求任何Vehicle的子類都必須提供這些方法的具體實現。這樣確保了所有的車輛類型都將具有這些基本行為，同時允許這些行為根據具體的車輛類型有不同的實現。

        2.提供具體實現：Car類作為Vehicle的一個子類，提供了drive和refuel方法的具體實現。這允許創建Car的實例並調用這些方法，展示了如何根據特定類型的車輛定制行為。
    
        3.易於擴展：這種設計使得新增更多種類的車輛（如摩托車、卡車等）變得非常簡單，只需繼承Vehicle類並實現相應的方法即可。每種車輛的特定行為可以根據其類型進行適當地定制，而不影響其他車輛或需要修改基礎抽象類別。
```
from abc import ABC, abstractmethod

class Vehicle(ABC):
    def __init__(self, make, model):
        self.make = make
        self.model = model

    @abstractmethod
    def drive(self):
        pass

    @abstractmethod
    def refuel(self):
        pass

class Car(Vehicle):
    def drive(self):
        print(f"The {self.make} {self.model} is driving.")

    def refuel(self):
        print(f"The {self.make} {self.model} is refueling.")

# 使用
my_car = Car("Toyota", "Corolla")
my_car.drive()
my_car.refuel()

```
- **不好的抽象化：**
在這個例子中，Car類包含了一個adjust_engine方法，這可能不是所有使用Car類的用戶都需要的功能。這個方法的存在使得Car類的抽象層次不夠好，因為它暴露了太多關於車輛內部機制的細節。這種設計可能會讓類的使用者感到困惑，並增加了使用錯誤的風險 , 以下為代碼解釋 

        1.過度具體化：這個Car類將所有車相關的功能（如駕駛、加油、調整引擎）都直接實現在同一個類中。這導致類的職責過於廣泛，不利於後續擴展或修改。例如，如果需要添加不同類型的車輛，如電動車，那麼refuel方法可能就不再適用，因為電動車不需要加油，而是需要充電。

        2.缺乏靈活性和擴展性：由於所有功能都緊密結合在Car類中，若要添加新的車輛類型或對現有行為進行修改，可能需要對Car類進行重大改動，這違反了開放封閉原則（OCP），即軟體實體應對擴展開放，對修改封閉。

        3.未利用繼承和多態性：這個設計未使用抽象類或接口來定義一個共通的行為接口，從而使不同類型的車輛能夠通過繼承和多態性來實現各自的特定行為。這限制了代碼重用和靈活性。

        4.緊密耦合的設計：Car類中的方法直接依賴於特定的屬性（如engine_code），這導致代碼之間耦合度增加，如果要更改引擎相關的設計，可能會影響到駕駛和加油的方法，從而增加維護成本。
```
class Car:
    def __init__(self, make, model, engine_code):
        self.make = make
        self.model = model
        self.engine_code = engine_code

    def drive(self):
        print(f"The {self.make} {self.model} with engine {self.engine_code} is driving.")

    def refuel(self):
        print(f"The {self.make} {self.model} is refueling.")

    def adjust_engine(self):
        print(f"Adjusting the engine {self.engine_code}.")

```
### (b) (15 points) Encapsulation
Encapsulation refers to a set of language-level mechanisms or design techniques that hide implementation details of a class, a module, or a subsystem from other classes, modules, and subsystems.

 - 好的封裝：把用戶的敏感資料（如密碼、個人隱私等）設置為私有的，只提供必要的介面來訪問或修改這些資料，以確保用戶資料的安全性和保密性。在以下例子裡，可發現GoodCar物件中的__make和__model變數都藉由getter和setter函數進行存取
```python=
class GoodCar:
    def __init__(self, make, model):
        self.__make = make
        self.__model = model
    
    def get_make(self):
        return self.__make
    
    def set_make(self, make):
        self.__make = make
    
    def get_model(self):
        return self.__model
    
    def set_model(self, model):
        self.__model = model
        
car = GoodCar('honda', 'accord')

print(car.get_make()) # output: honda
car.set_model('civic')
```

### Output

```shell
honda
```

- 不好的封裝：用戶的資料設置為公開的，或者提供過多的公開介面來訪問或修改這些資料，這樣會讓用戶資料的安全性受到威脅，也會讓程式的複雜度增加，增加了維護成本。下列代碼中可看出物件直接對BadCar的make和model進行更改，此時封裝就變成毫無意義了
```python=
class BadCar:
    def __init__(self, make, model):
        self.make = make
        self.model = model
        
car = BadCar('honda', 'accord')
car.make = "Toyota"
print(car.model) # output: accord
```

### Output

```shell
accord
```

### (c\) (15 points) Cohesion
Cohesion refers to the degree to which the elements inside a module belong together. It is a measure of the strength of relationship between the class's methods and data themselves.

- 好的內聚性：假設交友軟體中有一個用戶資料類別，它擁有用戶的基本資訊，例如姓名、年齡、性別、興趣、婚姻狀況等等。這些資訊在一個類別中是有內在關聯的並且需要的資料全部都包在一起的，所以這個用戶資料類別具有良好的內聚性，使得在這個類別中進行操作時更自然和直覺

### Source Code

```python3=
# 交友軟體用戶資料類別
class UserData:
    def __init__(self, name, age, gender, interests, marital_status):
        self.name = name # 姓名
        self.age = age # 年齡
        self.gender = gender # 性別
        self.interests = interests # 興趣
        self.marital_status = marital_status # 婚姻狀況

    def display_user_info(self):
        print(f"Name: {self.name}")
        print(f"Age: {self.age}")
        print(f"Gender: {self.gender}")
        print(f"Interests: {', '.join(self.interests)}")
        print(f"Marital Status: {self.marital_status}")

    def update_age(self, new_age):
        self.age = new_age

    def add_interest(self, new_interest):
        self.interests.append(new_interest)

if __name__ == "__main__":
    user1 = UserData("John Doe", 30, "Male", ["Reading", "Hiking"], "Single")
    user1.display_user_info()
    user1.update_age(31)
    user1.add_interest("Traveling")
    user1.display_user_info()
```

### Output

```
Name: John Doe
Age: 30
Gender: Male
Interests: Reading, Hiking
Marital Status: Single
Name: John Doe
Age: 31
Gender: Male
Interests: Reading, Hiking, Traveling
Marital Status: Single
```

- 不好的內聚性：假設交友軟體中有一個公開類別，其中包含了用戶資料、聊天記錄、好友列表、貼文資訊等等，這些內容之間並沒有內在關聯，因此這個類別的內聚性較低。這樣的類別設計可能會導致程式混亂，也會讓後續的維護與更新變得困難。

### Source Code

```python3=
class LowCohesionSocialApp:
    def __init__(self):
        self.user_data = {} // 用戶資料
        self.chat_records = [] // 聊天記錄
        self.friend_list = [] // 好友列表
        self.posts = [] // 貼文資訊

    def add_user(self, user_data):
        self.user_data[user_data["user_id"]] = user_data

    def add_chat_record(self, chat_record):
        self.chat_records.append(chat_record)

    def add_friend(self, friend_id):
        self.friend_list.append(friend_id)

    def add_post(self, post):
        self.posts.append(post)


low_cohesion_app = LowCohesionSocialApp()
low_cohesion_app.add_user({"user_id": 1, "name": "John Doe", "age": 30, "gender": "Male"})
low_cohesion_app.add_chat_record({"user_id": 1, "friend_id": 2, "message": "Hello!"})
low_cohesion_app.add_friend(2)
low_cohesion_app.add_post({"user_id": 1, "content": "Having a great day!"})
```

### Source Code


### (d) (15 points) Coupling
Coupling refers to the degree of interdependence between modules or classes in a system. Low coupling is desirable because it promotes better modularization, making the system easier to understand, maintain, and change. Here are examples of good and bad coupling:


#### Good Example of Low Coupling:
In this example, the Car class depends on an abstraction (Engine class) instead of a concrete implementation. The Car class is not tightly coupled to the Engine class; it only interacts with it through a well-defined interface. This promotes flexibility, as the Car class can easily work with different types of engines without needing modifications.

```python
class Engine:
    def start(self):
        return "Engine started"

class Car:
    def __init__(self, engine):
        self.engine = engine

    def start(self):
        return self.engine.start()

engine = Engine()
car = Car(engine)

print(car.start())  # Output: Engine started
```

#### Bad Example of High Coupling:

```python
class Car:
    def start(self):
        return "Engine started"

car = Car()

# Using the Car class
print(car.start())  # Output: Engine started
```

In this example, the Car class directly contains the functionality of starting the engine. This creates tight coupling between the Car class and the engine functionality. If there's a need to change how the engine starts or to use a different type of engine, changes will have to be made directly within the Car class, violating the principle of low coupling.

In summary, low coupling is desirable in object-oriented design as it promotes modularization, reusability, and maintainability. Classes should interact with each other through well-defined interfaces rather than directly depending on concrete implementations.

---

## 2. OOP Implements
以下是一個用Python實作的例子 ：
- (a) 抽象（Abstraction）：
代碼通過Shape類別建立了一個形狀的抽象，它定義了每個形狀應該具備的area和perimeter方法，但沒有提供實現。這允許程式碼中其他部分依賴於這些抽象而不是具體的實現。這體現了良好的使用，因為它使得增加新形狀變得容易而不需要改變與形狀交互的代碼。

- (b) 封裝（Encapsulation）：
每個形狀類別將其屬性（如半徑、長和寬）和與這些屬性相關的行為（如計算面積和周長的方法）封裝在一起。這保護了對象的內部狀態不被外部直接訪問，並通過方法對外提供了接口。

- (c) 內聚性（Cohesion）：
每個形狀類別都只關注於與該形狀相關的行為和屬性，例如，Circle類別只計算圓形的面積和周長。這表現了高內聚性，因為每個類別都只有單一的職責。

- (d) 耦合性（Coupling）：
在ShapeDatabase類別中，形狀對象通過它們的基類Shape接口相互操作，減少了類別間的耦合。這意味著形狀對象的具體類型對於ShapeDatabase來說是不重要的，只要它們遵循了Shape接口。這是一個耦合性低的好例子，因為增加新的形狀類型或更改現有形狀類型的實現不會影響ShapeDatabase。



function解釋 ：
Shape類別：是一個抽象基類，它定義了所有形狀共有的介面。具體來說，它定義了area()和perimeter()兩個方法，這兩個方法在基類中沒有實現，預期由子類提供具體的實現。

Circle類別：繼承自Shape類別，代表圓形。它實現了area()和perimeter()方法，用於計算圓形的面積和周長。__init__方法初始化類實例，設置圓形的半徑。

Rectangle類別：同樣繼承自Shape類別，代表矩形。它實現了area()和perimeter()方法，並通過__init__方法設置長和寬。__eq__方法用於比較兩個矩形是否相等。

Square類別：繼承自Rectangle類別，代表正方形。它重用了矩形的area()和perimeter()方法，因為正方形是邊長相等的矩形。__init__方法使用了super()函數來調用Rectangle的構造方法。

ShapeDatabase類別：這個類別用於管理形狀的集合。它包含一個添加形狀的add_shape()方法和一個顯示所有形狀面積和周長的display_all_shapes()方法。這個類實現了對形狀對象集合的封裝。

main函數：這是程式的主入口點。它創建了一個ShapeDatabase的實例，並將不同的形狀實例添加到這個"資料庫"中。然後，它調用display_all_shapes()方法來打印出每個形狀的面積和周長。

### Source Code

```python=
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
```

### Output

```
=====================
Shape:  Circle
Area: 78.53981633974483
Perimeter: 31.41592653589793
=====================

=====================
Shape:  Rectangle
Area: 24
Perimeter: 20
=====================

=====================
Shape:  Square
Area: 9
Perimeter: 12
=====================
```
