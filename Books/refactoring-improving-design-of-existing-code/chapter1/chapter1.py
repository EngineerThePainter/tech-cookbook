import json

from statement import statement


def main():
    plays = json.load(open('plays.json'))
    invoices = json.load(open('invoices.json'))
    for invoice in invoices:
        print(statement(invoice, plays))


if __name__ == "__main__":
    main()
