import Shapes

def main():
    x, y = 6, 2.3

    answer = Shapes.rectangle_area_py(x, y)
    print(f"In Python: int: {x} float {y:.1f} return val {answer:.1f}")

    rectangle = Shapes.Rectangle(12, 4, 50, 60)
    print(f"Rectangle x: {rectangle.get_x()}, y: {rectangle.get_y()}, width: {rectangle.get_width()}, height: {rectangle.get_height()}")

    rectangles = Shapes.get_rectangles()

    for r in rectangles:
        print(f"Rectangle x: {r.get_x()}, y: {r.get_y()}, width: {r.get_width()}, height: {r.get_height()}")
if __name__ == "__main__":
    main()