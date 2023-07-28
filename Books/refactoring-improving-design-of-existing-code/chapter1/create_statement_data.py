from math import floor


class PerformanceCalculator:
    def __init__(self, performance, play):
        self.performance = performance
        self.play = play

    def amount(self):
        if self.play['type'] == "tragedy":
            result = 40000
            if self.performance["audience"] > 30:
                result += 1000 * (self.performance["audience"] - 30)
        elif self.play['type'] == "comedy":
            result = 30000
            if self.performance["audience"] > 20:
                result += 10000 + 500 * (self.performance["audience"] - 20)
            result += 300 * self.performance["audience"]
        else:
            raise Exception(f"unknown type {self.play['type']}")
        return result

    def volume_credits(self):
        result = 0
        result += max(self.performance['audience'] - 30, 0)
        if "comedy" == self.play['type']:
            result += floor(self.performance['audience'] / 5)
        return result


def create_statement_data(invoice, plays):
    def play_for(performance):
        return plays[performance["playID"]]

    def volume_credits_for(performance):
        result = 0
        result += max(performance['audience'] - 30, 0)
        if "comedy" == performance['play']['type']:
            result += floor(performance['audience'] / 5)
        return result

    def enrich_perfomance(performance):
        calculator = PerformanceCalculator(performance, play_for(performance))
        result = performance.copy()
        result['play'] = calculator.play
        result['amount'] = calculator.amount()
        result['volume_credits'] = calculator.volume_credits()
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
