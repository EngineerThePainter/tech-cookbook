import json
import math


def amount_for(performance, play):
    if play['type'] == "tragedy":
        result = 40000
        if performance["audience"] > 30:
            result += 1000 * (performance["audience"] - 30)
    elif play['type'] == "comedy":
        result = 30000
        if performance["audience"] > 20:
            result += 10000 + 500 * (performance["audience"] - 20)
        result += 300 * performance["audience"]
    else:
        raise Exception(f"unknown type {play['type']}")
    return result


def statement(invoice, plays):
    total_amount = 0
    volume_credits = 0
    result = f"Statement for {invoice['customer']}\n"
    for perf in invoice['performances']:
        play = plays[perf['playID']]
        this_amount = amount_for(perf, play)
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
