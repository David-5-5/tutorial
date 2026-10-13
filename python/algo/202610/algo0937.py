class Solution:
    def reorderLogFiles(self, logs: list[str]) -> list[str]:
        log_d = []
        log_l = []

        for log in logs:
            for i, ch in enumerate(log):
                if ch == ' ':
                    if '0' <= log[i+1] <= '9':
                        log_d.append(log)
                    else:
                        log_l.append(log.split())
                    break
        
        log_l.sort(key=lambda row:(*row[1:], row[0]))


        return [" ".join(row) for row in log_l] + log_d