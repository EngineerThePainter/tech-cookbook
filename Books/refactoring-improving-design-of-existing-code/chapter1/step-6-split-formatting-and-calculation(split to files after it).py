import copy
import json
import math


def render_plain_text(data):
    result = f"Statement for {data['customer']}\n"

    for perf in data['performances']:
        result += f"    {perf['play']['name']}: ${usd(perf['amount'] / 100)} ({perf['audience']} seats)\n"

    result += f"Amount owned is ${usd(data['total_amount'] / 100)}\n"
    result += f"You earned {data['total_volume_credits']} credits\n"
    return result


def usd(number):
    return f"${number:.2f}$"


def create_statement_data(invoice, plays):
    def play_for(performance):
        return plays[performance["playID"]]

    def amount_for(performance):
        if performance['play']['type'] == "tragedy":
            result = 40000
            if performance["audience"] > 30:
                result += 1000 * (performance["audience"] - 30)
        elif performance['play']['type'] == "comedy":
            result = 30000
            if performance["audience"] > 20:
                result += 10000 + 500 * (performance["audience"] - 20)
            result += 300 * performance["audience"]
        else:
            raise Exception(f"unknown type {performance['play']['type']}")
        return result

    def volume_credits_for(performance):
        result = 0
        result += max(performance['audience'] - 30, 0)
        if "comedy" == performance['play']['type']:
            result += math.floor(performance['audience'] / 5)
        return result

    def enrich_perfomance(performance):
        result = performance.copy()
        result['play'] = play_for(result)
        result['amount'] = amount_for(result)
        result['volume_credits'] = volume_credits_for(result)
        return result

    def total_volume_credits(data):
        volume_credits = 0
        for perf in data['performances']:
            volume_credits += perf['volume_credits']
        return volume_credits

    def total_amount(data):
        result = 0
        for perf in data['performances']:
            result += perf['amount']
        return result

    statement_data = dict()
    statement_data['customer'] = invoice['customer']
    statement_data['performances'] = list(map(enrich_perfomance, invoice['performances']))
    statement_data['total_amount'] = total_amount(statement_data)
    statement_data['total_volume_credits'] = total_volume_credits(statement_data)
    return statement_data


def statement(invoice, plays):
    return render_plain_text(create_statement_data(invoice, plays))


def main():
    plays = json.load(open('plays.json'))
    invoices = json.load(open('invoices.json'))
    for invoice in invoices:
        print(statement(invoice, plays))


if __name__ == "__main__":
    main()
