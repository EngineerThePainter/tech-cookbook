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


def usd(number):
    return f"${number:.2f}$"


def volume_credits_for(performance):
    result = 0
    result += max(performance['audience'] - 30, 0)
    if "comedy" == play_for(performance)['type']:
        result += math.floor(performance['audience'] / 5)
    return result


def statement(invoice):
    total_amount = 0
    volume_credits = 0
    result = f"Statement for {invoice['customer']}\n"

    for perf in invoice['performances']:
        result += f"    {play_for(perf)['name']}: ${usd(amount_for(perf)/100)} ({perf['audience']} seats)\n"
        total_amount += amount_for(perf)

    for perf in invoice['performances']:
        volume_credits+= volume_credits_for(perf)

    result += f"Amount owned is ${usd(total_amount / 100)}\n"
    result += f"You earned {volume_credits} credits\n"
    return result


def main():
    for invoice in invoices:
        print(statement(invoice))


if __name__ == "__main__":
    main()
