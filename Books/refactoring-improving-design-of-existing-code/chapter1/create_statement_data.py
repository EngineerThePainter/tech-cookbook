from math import floor


class PerformanceCalculator:
    def __init__(self, performance, play):
        self.performance = performance
        self.play = play

    def amount(self):
        raise Exception("subclass responsibility")

    def volume_credits(self):
        return max(self.performance['audience'] - 30, 0)


class TragedyCalculator(PerformanceCalculator):
    def __init__(self, performance, play):
        super().__init__(performance, play)

    def amount(self):
        result = 40000
        if self.performance["audience"] > 30:
            result += 1000 * (self.performance["audience"] - 30)
        return result


class ComedyCalculator(PerformanceCalculator):
    def __init__(self, performance, play):
        super().__init__(performance, play)

    def amount(self):
        result = 30000
        if self.performance["audience"] > 20:
            result += 10000 + 500 * (self.performance["audience"] - 20)
        result += 300 * self.performance["audience"]
        return result

    def volume_credits(self):
        return super().volume_credits() + floor(self.performance["audience"] / 5)


def create_performance_calculator(performance, play):
    if play['type'] == "tragedy":
        return TragedyCalculator(performance, play)
    elif play['type'] == "comedy":
        return ComedyCalculator(performance, play)
    raise Exception(f"unknown type {play['type']}")


def create_statement_data(invoice, plays):
    def play_for(performance):
        return plays[performance["playID"]]

    def enrich_perfomance(performance):
        calculator = create_performance_calculator(performance, play_for(performance))
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
