from create_statement_data import create_statement_data


def render_plain_text(data):
    result = f"Statement for {data['customer']}\n"

    for perf in data['performances']:
        result += f"    {perf['play']['name']}: ${usd(perf['amount'] / 100)} ({perf['audience']} seats)\n"

    result += f"Amount owned is ${usd(data['total_amount'] / 100)}\n"
    result += f"You earned {data['total_volume_credits']} credits\n"
    return result


def usd(number):
    return f"${number:.2f}$"


def statement(invoice, plays):
    return render_plain_text(create_statement_data(invoice, plays))
