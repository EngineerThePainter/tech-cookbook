from math import floor

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
            result += floor(performance['audience'] / 5)
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