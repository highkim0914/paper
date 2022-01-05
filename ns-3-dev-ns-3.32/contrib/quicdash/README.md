## NS-3을 통한 QUIC 프로토콜의 비디오 스트리밍 성능
기존 DASH 모듈을 사용한 ["Simulation Framework for HTTP-Based Adaptive Streaming Application"](https://dl.acm.org/doi/10.1145/3067665.3067675)의 [소스코드](https://github.com/haraldott/dash)와 ns-3 내 quic을 구현한 ["A QUIC Implementation for ns-3"](https://arxiv.org/abs/1902.06121) 의 [소스코드](https://github.com/signetlabdei/quic-ns-3)를 활용하여 구현하였고 그를 통해 비디오 스트리밍 상황에서 TCP와 QUIC 사이의 성능을 분석하고 비교하였다.

## 결과
 
• 10, 50, 100Mbps 네트워크 설정 사용

• 대부분의 지표는 큰 차이가 없었으나 DASH 알고리즘에 따라 성능 차이 확인

• QUIC의 경우 시뮬레이션 초반 비디오 품질의 차이가 평균 품질에 영향, 최대 15%까지 달라짐.

• 특정 알고리즘의 경우 QUIC의 스트림 구조로 인해 좋지 않은 QoE로 이어짐.

![결과](https://github.com/highkim0914/paper/blob/main/ns-3-dev-ns-3.32/contrib/quicdash/esult.jpg)

• 추가 내용 [ppt](https://github.com/highkim0914/paper/edit/main/ns-3-dev-ns-3.32/contrib/quicdash/NS-3%EC%9D%84%20%ED%86%B5%ED%95%9C%20QUIC%20%ED%94%84%EB%A1%9C%ED%86%A0%EC%BD%9C%EC%9D%98%20%EB%B9%84%EB%94%94%EC%98%A4%20%EC%8A%A4%ED%8A%B8%EB%A6%AC%EB%B0%8D%20%EC%84%B1%EB%8A%A5.pptx)
