import json
import math


def statement(invoice, plays):
    total_amount = 0
    volume_credits = 0
    result = f"Statement for {invoice['customer']}\n"
    for perf in invoice['performances']:
        play = plays[perf['playID']]
        this_amount = 0
        if play['type'] == "tragedy":
            this_amount = 40000
            if perf["audience"] > 30:
                this_amount += 1000 * (perf["audience"] - 30)
        elif play['type'] == "comedy":
            this_amount = 30000
            if perf["audience"] > 20:
                this_amount += 10000 + 500 * (perf["audience"] - 20)
            this_amount += 300 * perf["audience"]
        else:
            raise Exception(f"unknown type {play['type']}")
        # add volume credits
        volume_credits += max(perf['audience'] - 30, 0)
        # add extra credit for every comedy ten attendees
        if "comedy" == play['type']:
            volume_credits += math.floor(perf['audience'] / 5)
        result += f"    {play['name']}: ${this_amount/100:.2f} ({perf['audience']} seats)\n"
        total_amount += this_amount
    result += f"Amount owned is ${total_amount/100:.2f}\n"
    result += f"You earned {volume_credits} credits\n"
    return result


def main():
    plays = json.load(open('plays.json'))
    invoices = json.load(open('invoices.json'))
    for invoice in invoices:
        print(statement(invoice, plays))


if __name__ == "__main__":
    main()
