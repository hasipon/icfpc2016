# icfpc2016

http://icfpc2016.blogspot.jp/

http://52.197.240.199:8000/

## requirements
- jq

## スナップショット更新
`./api-snapshot-list`

## 問題ダウンロード
`./problem-download`
現在のスナップショットに存在する問題をすべて `problems/` にダウンロードする

## problem2変換
`hasi/conv.sh`
`problems/` を `problems2/` に変換

## 完全一致検索
`hasi/getref.sh` , `hasi/solve_ref.sh` を順に実行。
`hasi/make_submit_ref.sh` を実行して得たコマンドを適当にsleep挟んだりして実行。

## 回答提出
`./solution-submit <problem_id> <path/to/solution>`  
提出ログが `solutions/` ディレクトリに残るので要コミット
