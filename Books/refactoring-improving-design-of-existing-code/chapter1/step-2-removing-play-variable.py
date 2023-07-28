import json
import math

plays = json.load(open('plays.json'))
invoices = json.load(open('invoices.json'))


def play_for(performance):
    return plays[performance["playID"]]


def amount_for(performance):
    if play_for(performance)['type'] == "tragedy":
        result = 40000
        if performance["audience"] > 30:
            result += 1000 * (performance["audience"] - 30)
    elif play_for(performance)['type'] == "comedy":
        result = 30000
        if performance["audience"] > 20:
            result += 10000 + 500 * (performance["audience"] - 20)
        result += 300 * performance["audience"]
    else:
        raise Exception(f"unknown type {play_for(performance)['type']}")
    return result


def statement(invoice):
    total_amount = 0
    volume_credits = 0
    result = f"Statement for {invoice['customer']}\n"
    for perf in invoice['performances']:
        # add volume credits
        volume_credits += max(perf['audience'] - 30, 0)
        # add extra credit for every comedy ten attendees
        if "comedy" == play_for(perf)['type']:
            volume_credits += math.floor(perf['audience'] / 5)
        result += f"    {play_for(perf)['name']}: ${amount_for(perf)/100:.2f} ({perf['audience']} seats)\n"
        total_amount += amount_for(perf)
    result += f"Amount owned is ${total_amount/100:.2f}\n"
    result += f"You earned {volume_credits} credits\n"
    return result


def main():

    for invoice in invoices:
        print(statement(invoice))


if __name__ == "__main__":
    main()
