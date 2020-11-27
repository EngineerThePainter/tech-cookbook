import Shapes

def main():
    x, y = 6, 2.3

    answer = Shapes.rectangle_area_py(x, y)
    print(f"    In Python: int: {x} float {y:.1f} return val {answer:.1f}")

if __name__ == "__main__":
    main()